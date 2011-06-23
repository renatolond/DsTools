void run()
{
    init();

    for(;;)
    {
        PA_WaitForVBlank();
        render();

        if(!update())
            break;
    }

    cleanup();
}

