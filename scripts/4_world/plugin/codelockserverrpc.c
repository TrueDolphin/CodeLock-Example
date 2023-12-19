modded class CodeLockServerRPC
{
    
    private void OpenTarget(ItemBase target)
    {
        //hate this is private and not an override
        Example_Base eb = Example_Base.Cast(target);

        if (eb && !eb.IsOpen()) 
        {
            eb.Open();
        }
        super.OpenTarget(target);
    }
};