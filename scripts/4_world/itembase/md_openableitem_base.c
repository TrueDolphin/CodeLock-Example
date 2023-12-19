modded class Example_Base
{
    override bool CanReceiveAttachment(EntityAI attachment, int slotId)
    {
        CodeLock Lock;
        if (Class.CastTo(Lock, attachment)) return true;

        return super.CanReceiveAttachment(attachment, slotId);
    }

    override void SetActions()
    {
        super.SetActions();
        AddAction(ActionInteractLockOnEB);
        AddAction(ActionManageLockOnEB);
        AddAction(ActionLockAdminOnEB);
    }
};