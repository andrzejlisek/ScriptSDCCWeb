let StorageMemo = [];

let StorageMemoCode = [];

function StoragePrefixScript(N)
{
    if ((N >= 0) && (N <= 255))
    {
        return StoragePrefix + "Script" + NumToHex8(N);
    }
    else
    {
        return StoragePrefix + "Script__";
    }
}


let StorageScriptCount = 0;


function StorageMemoValueSave(N)
{
    StorageMemoValue(N);
    //DataSet(StoragePrefixScript(999) + "Code", GuiStringEncode(StorageMemoCode_ctrl.value));
    DataSet(StoragePrefixScript(999) + "Machine", StorageMemoMachine_ctrl.selectedIndex);
    DataSet(StoragePrefixScript(999) + "MachineMem", StorageMemoMachineMem_ctrl.selectedIndex);
    DataSet(StoragePrefixScript(999) + "SwapPage", ValueInt(StorageMemoSwapPage_ctrl.value));
}


function StorageMemoValue(N)
{
    let CtrlName = "";
    switch (N)
    {
        case 5: CtrlName = "StorageMemoSwapPage"; break;
    }
    if (N > 0)
    {
        document.getElementById(CtrlName + "_").innerHTML = " = " + NumToHex8(ValueInt(document.getElementById(CtrlName).value));
    }
}

function StorageSomethingRunning()
{
    for (let I = 0; I < StorageMemoCode.length; I++)
    {
        if (StorageMemo[I].Running)
        {
            return true;
        }
    }
    return false;
}

function StorageInit()
{
    for (let I = 0; I < 256; I++)
    {
        StorageMemo[I] = {};
        StorageMemo[I].Code = "";
        StorageMemo[I].Machine = 0;
        StorageMemo[I].MachineMem = 0;
        StorageMemo[I].SwapPage = 0x7F;
        StorageMemo[I].Running = false;
        StorageMemo[I].CodeExists = false;
        StorageMemo[I].Entry = "X";
        StorageMemo[I].StatusC = 0;
        StorageMemo[I].ErrorMsg = "";
        MemoPrepare(I);
        TimingPrepare(I);
    }


    StorageMemoSwapPage_ctrl.value = "0";

    StorageMemoValue(5);

    StorageListLoad();
    
    StorageScriptCount = DataGetIDefault(StoragePrefix + "ScriptCount", 0);
    
    for (let I = 0; I < StorageScriptCount; I++)
    {
        let Opt = document.createElement("option");
        Opt.text = DataGetDefault(StoragePrefixScript(I) + "Name", "Script" + NumToHex8(I));
        StorageList_ctrl.add(Opt);
    }
}


function StorageCodeClear()
{
    StorageMemoCode_ctrl.value = "";
}

function StorageCodeCopy()
{
    if (navigator.clipboard.writeText)
    {
        navigator.clipboard.writeText(StorageMemoCode_ctrl.value);
    }
}

function StorageCodePaste()
{
    StorageCodeClear();
    if (navigator.clipboard.readText)
    {
        navigator.clipboard.readText().then(clipText => StorageCodePaste2(clipText)).catch(error => StorageCodePaste3(error));
    }
    else
    {
    }
}

function StorageCodePaste2(Text)
{
    StorageMemoCode_ctrl.value = Text;
}

function StorageCodePaste3(Text)
{
}


function StorageListSave()
{
    const Idx = StorageList_ctrl.selectedIndex;
    let ScriptName = "";
    if (Idx >= 0)
    {
        ScriptName = StorageList_ctrl[Idx].text;
    }
    ScriptName = prompt("Script name", ScriptName);
    if (ScriptName)
    {
        let Idx = -1;
        for (let I = 0; I < StorageScriptCount; I++)
        {
            if (DataGetDefault(StoragePrefixScript(I) + "Name", "") == ScriptName)
            {
                Idx = I;
            }
        }
        if (Idx < 0)
        {
            Idx = StorageScriptCount;
            let Opt = document.createElement("option");
            Opt.text = ScriptName;
            StorageList_ctrl.add(Opt);
            StorageScriptCount++;
            StorageList_ctrl.selectedIndex = Idx;
        }
        if ((Idx >= 0) && (Idx <= 255))
        {
            DataSet(StoragePrefix + "ScriptCount", StorageScriptCount);
            DataSet(StoragePrefixScript(Idx) + "Name", ScriptName);
            DataSet(StoragePrefixScript(Idx) + "Code", GuiStringEncode(StorageMemoCode_ctrl.value));
            DataSet(StoragePrefixScript(Idx) + "Machine", StorageMemoMachine_ctrl.selectedIndex);
            DataSet(StoragePrefixScript(Idx) + "MachineMem", StorageMemoMachineMem_ctrl.selectedIndex);
            DataSet(StoragePrefixScript(Idx) + "SwapPage", ValueInt(StorageMemoSwapPage_ctrl.value));
        }
    }
}

function StorageListLoad()
{
    const Idx = StorageList_ctrl.selectedIndex;
    StorageMemoCode_ctrl.value = GuiStringDecode(DataGetDefault(StoragePrefixScript(Idx) + "Code", ""));
    StorageMemoMachine_ctrl.selectedIndex = DataGetIDefault(StoragePrefixScript(Idx) + "Machine", 0);
    StorageMemoMachineMem_ctrl.selectedIndex = DataGetIDefault(StoragePrefixScript(Idx) + "MachineMem", 0);
    StorageMemoSwapPage_ctrl.value = DataGetIDefault(StoragePrefixScript(Idx) + "SwapPage", 0x7F);

    StorageMemoValueSave(5);
}

function StorageListItemCopy(Src, Dst)
{
    DataSet(StoragePrefixScript(Dst) + "Name",       DataGetDefault(StoragePrefixScript(Src) + "Name", ""));
    DataSet(StoragePrefixScript(Dst) + "Code",       DataGetDefault(StoragePrefixScript(Src) + "Code", ""));
    DataSet(StoragePrefixScript(Dst) + "Machine",    DataGetDefault(StoragePrefixScript(Src) + "Machine", ""));
    DataSet(StoragePrefixScript(Dst) + "MachineMem", DataGetDefault(StoragePrefixScript(Src) + "MachineMem", ""));
    DataSet(StoragePrefixScript(Dst) + "SwapPage",   DataGetDefault(StoragePrefixScript(Src) + "SwapPage", ""));
}

function StorageListItemDelete(Idx)
{
    DataDelete(StoragePrefixScript(Idx) + "Name");
    DataDelete(StoragePrefixScript(Idx) + "Code");
    DataDelete(StoragePrefixScript(Idx) + "Machine");
    DataDelete(StoragePrefixScript(Idx) + "MachineMem");
    DataDelete(StoragePrefixScript(Idx) + "SwapPage");
}

function StorageListRemove()
{
    let Idx = StorageList_ctrl.selectedIndex;
    if (Idx >= 0)
    {
        if (confirm("Remove \"" + DataGetDefault(StoragePrefixScript(Idx) + "Name", "") + "\"?"))
        {
            StorageScriptCount = StorageScriptCount - 1;
            for (let I = Idx; I < StorageScriptCount; I++)
            {
                StorageListItemCopy(Idx + 1, Idx);
            }

            Idx = StorageScriptCount;
            DataSet(StoragePrefix + "ScriptCount", StorageScriptCount);
            StorageListItemDelete(Idx);
            StorageList_ctrl.remove(Idx);
            StorageListLoad();
        }
    }
}

function StorageListMoveU()
{
    const Idx = StorageList_ctrl.selectedIndex;
    if ((Idx >= 1) && (Idx < StorageScriptCount))
    {
        StorageListItemCopy(Idx, StorageScriptCount);
        StorageListItemCopy(Idx - 1, Idx);
        StorageListItemCopy(StorageScriptCount, Idx - 1);
        StorageListItemDelete(StorageScriptCount);

        const Temp = StorageList_ctrl[Idx].text;
        StorageList_ctrl[Idx].text = StorageList_ctrl[Idx - 1].text;
        StorageList_ctrl[Idx - 1].text = Temp;
        
        StorageList_ctrl.selectedIndex = StorageList_ctrl.selectedIndex - 1;
    }
}

function StorageListMoveD()
{
    const Idx = StorageList_ctrl.selectedIndex;
    if ((Idx >= 0) && (Idx < (StorageScriptCount - 1)))
    {
        StorageListItemCopy(Idx, StorageScriptCount);
        StorageListItemCopy(Idx + 1, Idx);
        StorageListItemCopy(StorageScriptCount, Idx + 1);
        StorageListItemDelete(StorageScriptCount);

        const Temp = StorageList_ctrl[Idx].text;
        StorageList_ctrl[Idx].text = StorageList_ctrl[Idx + 1].text;
        StorageList_ctrl[Idx + 1].text = Temp;
        
        StorageList_ctrl.selectedIndex = StorageList_ctrl.selectedIndex + 1;
    }
}


StorageInit();

