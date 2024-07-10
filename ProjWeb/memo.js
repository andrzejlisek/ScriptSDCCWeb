function MemoPrepare(N)
{
    StorageMemo[N].MemoryMap = [];
    MemoPaintReset(N);
}

function MemoLoad(N)
{
    if (StorageMemo[N].Running)
    {
        return;
    }
    
    StorageMemo[N].Machine = StorageMemoMachine_ctrl.selectedIndex;
    StorageMemo[N].MachineMem = StorageMemoMachineMem_ctrl.selectedIndex;
    StorageMemo[N].SwapPage = ValueInt(StorageMemoSwapPage_ctrl.value);
    StorageMemo[N].ErrorMsg = "";
    MemoPrepare(N);
    let LengthThreshold = 10000;
    let CodeStr = StorageMemoCode_ctrl.value;
    let MachineId = StorageMemoMachine_ctrl.selectedIndex + (StorageMemoMachineMem_ctrl.selectedIndex * 3);
    if (CodeStr.length <= LengthThreshold)
    {
        _ProgCodeLoad(N, LayoutConfInstrQuan, MachineId, CodeStr, "", ValueInt(StorageMemoSwapPage_ctrl.value));
    }
    else
    {
        _ProgCodeLoad(N, LayoutConfInstrQuan, MachineId, "", "", ValueInt(StorageMemoSwapPage_ctrl.value));
        while (CodeStr.length > LengthThreshold)
        {
            _ProgCodeLoad(N, 0, 101, CodeStr.substr(0, LengthThreshold), "", ValueInt(StorageMemoSwapPage_ctrl.value));
            CodeStr = CodeStr.substr(LengthThreshold);
        }
        if (CodeStr.length > 0)
        {
            _ProgCodeLoad(N, 0, 101, CodeStr, "", ValueInt(StorageMemoSwapPage_ctrl.value));
        }
        _ProgCodeLoad(N, LayoutConfInstrQuan, 102, "", "", ValueInt(StorageMemoSwapPage_ctrl.value));
    }
}


function MemoResetBtn(N)
{
    if (!StorageMemo[N].Running)
    {
        MemoReset(N);
    }
}

function MemoReset(N)
{
    StorageMemo[N].ErrorMsg = "";
    _ProgCodeReset(N, 0);
}

function MemoStartBtn(N)
{
    if (StorageMemo[N].Running)
    {
        return;
    }
    TimingReset(N);
    StorageMemo[N].Running = true;
    _ProgCodeStart(N);
}

function MemoStopBtn(N)
{
    if (!StorageMemo[N].Running)
    {
        return;
    }
    _ProgCodeStop(N);
}

function MemoDecompileBtn(N)
{
    const EntryPoints = StorageMemo[N].Entry;
    
    if (EntryPoints.length > 3)
    {
        const Pts = EntryPoints.split('X');
        const Addr = prompt("Start: " + Pts[1] + "\nInt 1: " + Pts[2] + "\nInt 2: " + Pts[3], Pts[1]);
        if (Addr)
        {
            const AddrNum = HexToNum(Addr);
            if ((AddrNum >= 0) && (AddrNum < 65536))
            {
                _ProgMemoMap(N, 16, 6 + (AddrNum * 16));
            }
        }
    }
    else
    {
        alert("Engine " + N + ": Code not exists");
    }
}

function MemoPaintBtn(N)
{
    GuiOpenMemo(N)
}

function XMemoScriptMessage(Msg)
{
    const N = HexToNum8(Msg.substr(1, 2));
    if (Msg[0] == 'D')
    {
        console.log(N + ": " + GuiStringDecode(Msg.substr(3)));
    }
    if (Msg[0] == 'E')
    {
        StorageMemo[N].ErrorMsg = Msg.substr(3);
    }
}

function MemoDecom(MemoMapText)
{
    MemoMapText = MemoMapText.substr(5);
    if (MemoMapText.length > 5)
    {
        if (MemoMapText[0] == '*')
        {
            console.log("                     _" + MemoMapText.substr(1, 4) + ":");
        }
        console.log(MemoMapText.substr(1));
    }
}

function MemoPaint(MemoMapText)
{
    if (MemoMapText[3] != '!')
    {
        const MemoPaintNumber = HexToNum(MemoMapText.substr(1, 2));
        const MemoPaintPage = HexToNum(MemoMapText.substr(3, 2));
    
        StorageMemo[MemoPaintNumber].MemoryMap[MemoPaintPage] = MemoMapText;
        GuiMemoPaint(MemoPaintNumber, MemoPaintPage);
    }
}

function MemoPaintReset(N)
{
    let Hex_ = "0123456789ABCDEF";
    let DummyMemMap = "AAAAAAAAAAAAAAAA";
    DummyMemMap = DummyMemMap + DummyMemMap;
    DummyMemMap = DummyMemMap + DummyMemMap;
    DummyMemMap = DummyMemMap + DummyMemMap;
    DummyMemMap = DummyMemMap + DummyMemMap;
    for (let II = 0; II < 16; II++)
    {
        for (let I = 0; I < 16; I++)
        {
            MemoPaint("_" + NumToHex8(N) + Hex_[II] + Hex_[I] + DummyMemMap);
        }
    }
}



function MemoMapInit()
{
    for (let I = 0; I < 256; I++)
    {
        MemoMap[I] = [];
    }
}

