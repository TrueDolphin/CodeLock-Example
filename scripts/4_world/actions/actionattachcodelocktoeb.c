class ActionAttachCodeLockToEB : ActionSingleUseBase
{
    override void CreateConditionComponents()
    {
        m_ConditionItem = new CCINonRuined;
        m_ConditionTarget = new CCTNone;
    }

    override string GetText()
    {
        return "Attach";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        Example_Base eb = Example_Base.Cast(target.GetObject());
        if (eb && !eb.IsLocked() && !eb.IsCodeLocked()) return true;
        return false;
    }

    override void OnExecuteClient(ActionData action_data)
    {
        Example_Base eb = Example_Base.Cast(action_data.m_Target.GetObject());
        PlayerBase player = action_data.m_Player;
		ClearInventoryReservationEx(action_data);
        if (eb)
        {
            InventorySlots slots = new InventorySlots;
            int slotID = slots.GetSlotIdFromString(CLConst.clAttachment);

            action_data.m_Player.PredictiveTakeEntityToTargetAttachmentEx(eb, action_data.m_MainItem, slotID);
            GetCLUIManager().ShowMenu(CLMENU.SET_CODE_MENU, eb);
        }
    }

    override void OnExecuteServer(ActionData action_data)
    {
        Example_Base eb = Example_Base.Cast(action_data.m_Target.GetObject());
        PlayerIdentity id = action_data.m_Player.GetIdentity();
        if (eb && id)
        {
            GetCodeLockLogger().WriteLog("attached", id, eb.GetPosition());
        }
    }
};