modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);

        actions.Insert(ActionDestroyCodeLockOnEB);
        actions.Insert(ActionInteractLockOnEB);
        actions.Insert(ActionAttachCodeLockToEB);
        actions.Insert(ActionManageLockOnEB);
        actions.Insert(ActionLockAdminOnEB);
    }
};