void Pre_LoadingProcess()
    {
        tempStorage.clear();
        tempStorage = " THE REPORT FOR month IS BEING GENERATED ";

        int i=1;
        do
        {
            scrClr();
            setCursorPos(12,10);
            SetColor(1);
            ShowConsoleCursor(false);
            cout<<tempStorage;
            scrClr(2);
            tempStorage = tempStorage + " ! ";

            if(process_flag||i==15)
            {
                break;
            }
            i++;

        } while (true);
        
        
        tempStorage.clear();
        SetColor(0);
        scrClr(0.5);
    }