class ActionInteractLockOnEB : ActionInteractBase
{
    string lockState;

    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINone;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText()
    {
        return lockState;
    }

    override bool IsInstant()
    {
        return true;
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Example_Base eb = Example_Base.Cast(target.GetObject());
        CodeLock codelock;

        if (eb && !eb.IsOpen())
        {
            codelock = CodeLock.Cast(eb.GetCodeLock());

            if (codelock)
            {
                bool isOwner = codelock.IsOwner(player.GetIdentity().GetId());
                bool isGuest = codelock.IsGuest(player.GetIdentity().GetId());

                if (player && !GetDayZGame().CLIsActionRateLimited())
                {
                    auto params = new Param1<CodeLock>(codelock);
                    GetGame().RPCSingleParam(player, CLRPC.RPC_SERVER_SYNCHLOCK, params, true);
                    GetDayZGame().SetCLActionRateLimit();
                }
                if (codelock.GetLockState())
                {
                    if (isOwner || isGuest)
                    {
                        lockState = "Open Locked Door";
                    }
                    else if (!codelock.HasNoOwner())
                    {
                        lockState = "Enter Passcode";
                    }
                    else
                    {
                        return false;
                    }
                }
                else
                {
                    lockState = "Set Passcode";
                }
                return true;
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        EntityAI targetObject = action_data.m_Target.GetObject();
        Example_Base eb = Example_Base.Cast(targetObject);
        CodeLock codelock;

        if (eb)
        {
            codelock = CodeLock.Cast(eb.GetCodeLock());

            if (codelock)
            {
                if (codelock.GetLockState())
                {
                    if (!codelock.IsOwner(identity.GetId()) && !codelock.IsGuest(identity.GetId()))
                    {
                        GetCLUIManager().ShowMenu(CLMENU.GUEST_CODE_MENU, targetObject);
                    }
                }
                else
                {
                    GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, targetObject);
                }
            }
        }
    }

    override void OnStartServer(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        Example_Base eb = Example_Base.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (eb)
        {
            codelock = CodeLock.Cast(eb.GetCodeLock());

            if (codelock)
            {
                if (codelock.GetLockState() && (codelock.IsOwner(identity.GetId()) || codelock.IsGuest(identity.GetId())))
                {
                    GetCodeLockLogger().WriteLog("accessed", action_data.m_Player.GetIdentity(), codelock.GetPosition());
                    eb.Open();
                }
            }
        }
    }
};