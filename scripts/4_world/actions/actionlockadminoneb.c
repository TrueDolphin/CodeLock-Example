class ActionLockAdminOnEB : ActionInteractBase
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

            if (codelock && codelock.GetLockState() && GetCLPermissionManager().UserIsAdmin(player.GetIdentity().GetPlainId())
            {
                lockState = "Admin Lock";
                return true;
            }
        }
        return false;
    }

    override void OnStartClient(ActionData action_data)
    {
        PlayerBase player = action_data.m_Player;
        PlayerIdentity identity = player.GetIdentity();
        Example_Base eb = Example_Base.Cast(action_data.m_Target.GetObject());
        CodeLock codelock;

        if (eb)
        {
            codelock = CodeLock.Cast(eb.GetCodeLock());

            if (codelock && codelock.GetLockState() && GetCLPermissionManager().UserIsAdmin())
            {
                GetCLUIManager().ShowMenu(CLMENU.ADMIN_CODE_MENU, eb);
            }
        }
    }
};