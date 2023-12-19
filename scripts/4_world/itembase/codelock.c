modded class CodeLock
{      
    override void NewUnlockServer(EntityAI player, EntityAI parent)
    {
        if (!GetGame().IsServer() || !GetGame().IsMultiplayer())
            return;
        Example_Base baseItem = Example_Base.Cast(parent);
        if (baseItem)
        {
            baseItem.Open();
            
            player.ServerDropEntity( this );
            SetPosition(player.GetPosition());
        }

        super.NewUnlockServer(player, parent);
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionAttachCodeLockToEB);
    }
};