let GuiIdThis = Date.now();

function GuiGetId()
{
    return GuiIdThis;
}

// Widows types:
//  0 - Dead or unknown
//  1 - Widgets
//  2 - Graphics
let GuiOpenedWindows = [];

function GuiOpenWidgets(Num)
{
    let WinDef = [];
    WinDef[0] = 11;
    WinDef[1] = Num;
    WinDef[2] = GuiNewWindow("guiwidgets.html");
    WinDef[3] = 0;
    GuiOpenedWindows.push(WinDef);
    GuiWindowSync(GuiOpenedWindows.length - 1);
}


function GuiOpenGraph(Num)
{
    let WinDef = [];
    WinDef[0] = 12;
    WinDef[1] = Num;
    WinDef[2] = GuiNewWindow("guigraph.html");
    WinDef[3] = 0;
    GuiOpenedWindows.push(WinDef);
    GuiWindowSync(GuiOpenedWindows.length - 1);
}


function GuiOpenMemo(Num)
{
    let WinDef = [];
    WinDef[0] = 13;
    WinDef[1] = Num;
    WinDef[2] = GuiNewWindow("guimemo.html");
    WinDef[3] = 0;
    GuiOpenedWindows.push(WinDef);
    GuiWindowSync(GuiOpenedWindows.length - 1);
}


function GuiWindowSync(Idx)
{
    if (GuiOpenedWindows[Idx][2])
    {
        if ((GuiOpenedWindows[Idx][2].GetId) && (!GuiOpenedWindows[Idx][2].closed))
        {
            if (GuiOpenedWindows[Idx][2].GetId())
            {
                GuiOpenedWindows[Idx][3] = GuiOpenedWindows[Idx][2].SyncId(GuiIdThis, GuiOpenedWindows[Idx][1], Idx);
                if (GuiOpenedWindows[Idx][0] > 10)
                {
                    GuiOpenedWindows[Idx][0] = GuiOpenedWindows[Idx][0] - 10;
                    if (GuiOpenedWindows[Idx][0] == 1)
                    {
                        GuiOpenedWindows[Idx][2].SetWidgetFontSize(LayoutConfWidgetFontSize);
                        _ProgWidgetRefresh(GuiOpenedWindows[Idx][1], Idx);
                    }
                    if (GuiOpenedWindows[Idx][0] == 2)
                    {
                        GuiOpenedWindows[Idx][2].SetLayout(LayoutButtonHeight);
                    }
                    if (GuiOpenedWindows[Idx][0] == 3)
                    {
                        GuiMemoPaintWhole(GuiOpenedWindows[Idx][1], Idx);
                    }
                }
                return;
            }
        }
    }
    setTimeout(function() { GuiWindowSync(Idx); }, 100);
}


function GuiCheckAlive(Idx, WindowType)
{
    if (GuiOpenedWindows[Idx][0] != WindowType) return false;

    let WindowAlive = false;    
    if (GuiOpenedWindows[Idx][2].GetId && (!GuiOpenedWindows[Idx][2].closed))
    {
        if (GuiOpenedWindows[Idx][2].GetId() == GuiOpenedWindows[Idx][3])
        {
            WindowAlive = true;
        }
    }
    if (!WindowAlive)
    {
        if ((GuiOpenedWindows[Idx][0] < 10))
        {
            GuiOpenedWindows[Idx][0] = 0;
        }
    }
    return WindowAlive;
}

function GuiNewWindow(HtmlUrl)
{
    let WinDeltaX = window.outerWidth  - window.innerWidth;
    let WinDeltaY = window.outerHeight - window.innerHeight;
    if (WinDeltaX > (window.innerWidth  /  2)) { WinDeltaX = parseInt((window.innerWidth  /  2)); }
    if (WinDeltaY > (window.innerHeight /  2)) { WinDeltaY = parseInt((window.innerHeight /  2)); }
    if (WinDeltaX < (window.outerWidth  / 20)) { WinDeltaX = parseInt((window.outerWidth  / 20)); }
    if (WinDeltaY < (window.outerHeight / 20)) { WinDeltaY = parseInt((window.outerHeight / 20)); }
    const WinX = window.screenX + WinDeltaX;
    const WinY = window.screenY + WinDeltaY;
    const WinW = DebugMode ? (800 + 0) : (window.outerWidth - WinDeltaX - WinDeltaX);
    const WinH = DebugMode ? (600 + 1) : (window.outerHeight - WinDeltaY - WinDeltaY);
    return window.open(HtmlUrl, "_blank", "left=" + WinX + "px,top=" + WinY + "px,width=" + WinW + "px,height=" + WinH + "px");
}


function GuiWidgetClear_(I)
{
    if (GuiCheckAlive(I, 1))
    {
        GuiOpenedWindows[I][2].WidgetClear();
    }
}

function GuiWidgetClear(N)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (GuiCheckAlive(I, 1) && (GuiOpenedWindows[I][1] == N))
        {
            GuiOpenedWindows[I][2].WidgetClear();
        }
    }
}

function GuiWidgetAdd_(I, Id, ParId)
{
    if (GuiCheckAlive(I, 1))
    {
        GuiOpenedWindows[I][2].WidgetAdd(Id, ParId);
    }
}

function GuiWidgetAdd(N, Id, ParId)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (GuiCheckAlive(I, 1) && (GuiOpenedWindows[I][1] == N))
        {
            GuiOpenedWindows[I][2].WidgetAdd(Id, ParId);
        }
    }
}

function GuiWidgetRemove(N, Id)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (GuiCheckAlive(I, 1) && (GuiOpenedWindows[I][1] == N))
        {
            GuiOpenedWindows[I][2].WidgetRemove(Id);
        }
    }
}

function GuiWidgetParamSet_(I, Id, Param, Value)
{
    if (GuiCheckAlive(I, 1))
    {
        GuiOpenedWindows[I][2].WidgetParamSet(Id, Param, GuiStringDecode(Value));
    }
}

function GuiWidgetParamSet(N, Id, Param, Value)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (GuiCheckAlive(I, 1) && (GuiOpenedWindows[I][1] == N))
        {
            GuiOpenedWindows[I][2].WidgetParamSet(Id, Param, GuiStringDecode(Value));
        }
    }
}

function GuiWidgetEvent(Idx, N, WidgetId, WidgetValue)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (I != Idx)
        {
            if (GuiCheckAlive(I, 1) && (GuiOpenedWindows[I][1] == N))
            {
                GuiOpenedWindows[I][2].WidgetParamSet(WidgetId, 0, WidgetValue);
            }
        }
    }
    _ProgWidgetInvokeEvent(N, WidgetId, 1, WidgetValue);
}

function GuiWidgetEventProgWork(N, WidgetId)
{
    _ProgWidgetInvokeEvent(N, WidgetId, 0, "");
}

function GuiWidgetEventProg(N, WidgetId)
{
    setTimeout(function() { GuiWidgetEventProgWork(N, WidgetId); }, 1);
}

function GuiStringEncode(Txt)
{
    for (let I = 0; I < Txt.length; I++)
    {
        let NonStdChar = true;
        if ((Txt[I] >= '0') && (Txt[I] <= '9')) { NonStdChar = false; }
        if ((Txt[I] >= 'A') && (Txt[I] <= 'Z')) { NonStdChar = false; }
        if ((Txt[I] >= 'a') && (Txt[I] <= 'z')) { NonStdChar = false; }
        if (NonStdChar)
        {
            let ChrX = Txt.charCodeAt(I);
            if (ChrX < 0) ChrX += 256;
            if (ChrX < 256)
            {
                Txt = Txt.substr(0, I) + "%" + NumToHex8(ChrX) + Txt.substr(I + 1);
                I += 2;
            }
            else
            {
                Txt = Txt.substr(0, I) + "_" + NumToHex16(ChrX) + Txt.substr(I + 1);
                Txt[I] = '_';
                I += 4;
            }
        }
    }
    return Txt;
}

function GuiStringDecode(Txt)
{
    for (let I = 0; I < Txt.length; I++)
    {
        if (Txt[I] == '%')
        {
            Txt = Txt.substr(0, I) + String.fromCharCode(HexToNum(Txt.substr(I + 1, 2))) + Txt.substr(I + 3);
        }
        else
        {
            if (Txt[I] == '_')
            {
                Txt = Txt.substr(0, I) + String.fromCharCode(HexToNum(Txt.substr(I + 1, 4))) + Txt.substr(I + 5);
            }
        }
    }
    return Txt;
}


function GuiGraphSetParams(N, Idx, ParamN, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9)
{
    _ProgGraphSetParams(N, Idx, ParamN, P0, P1, P2, P3, P4, P5, P6, P7, P8, P9);
}

function GuiGraphClear(Idx, N, ScrW, ScrH)
{
    _ProgGraphClearScreen(N, Idx, ScrW, ScrH);
}

function GuiGraphRepaint(Idx, N, ScrW, ScrH)
{
    _ProgGraphRepaintScreen(N, Idx, ScrW, ScrH);
}

function GuiGraphRepaintResult(Idx, DataIdx, DataRaw, DataRawL)
{
    if (GuiCheckAlive(Idx, 2))
    {
        GuiOpenedWindows[Idx][2].RepaintResult(DataIdx, DataRaw, DataRawL);
    }
}

function GuiGraphRepaintResultFinish(Idx)
{
    if (GuiCheckAlive(Idx, 2))
    {
        GuiOpenedWindows[Idx][2].RepaintResultFinish();
    }
}

let GuiGraphRepaintLast = 0;

function GuiGraphRepaintAll()
{
    if ((GuiGraphRepaintLast + GuiGraphRepaintPeriod) > performance.now())
    {
        return;
    }
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        GuiGraphRepaintLast = performance.now();
        if (GuiCheckAlive(I, 2))
        {
            const CanvasWH = GuiOpenedWindows[I][2].CanvasWH();
            GuiGraphRepaint(I, GuiOpenedWindows[I][1], CanvasWH[0], CanvasWH[1]);
        }
        if (GuiCheckAlive(I, 3))
        {
            _ProgMemoMap(GuiOpenedWindows[I][1], 8, 0);
        }
    }
    GuiGraphRepaintLast = performance.now();
}


function GuiGraphRepaintAllTimer()
{
    if (!StorageSomethingRunning())
    {
        GuiGraphRepaintAll();
        setTimeout(GuiGraphRepaintAllTimer, GuiGraphRepaintPeriod);
    }
}

function GuiMemoPaintOnePage(I, N, Page)
{
    const MemoCommon = (StorageMemo[N].MachineMem == 0);
    const MemoSwapPage = StorageMemo[N].SwapPage;
    GuiOpenedWindows[I][2].PaintMemo(StorageMemo[N].MemoryMap[Page], MemoCommon, MemoSwapPage);
}

function GuiMemoPaintWhole(N, Idx)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (GuiCheckAlive(I, 3))
        {
            if (GuiOpenedWindows[I][1] == N)
            {
                for (let Page = 0; Page < 256; Page++)
                {
                    GuiMemoPaintOnePage(I, N, Page);
                }
            }
        }
    }
}

function GuiMemoPaint(N, Page)
{
    for (let I = 0; I < GuiOpenedWindows.length; I++)
    {
        if (GuiCheckAlive(I, 3))
        {
            if (GuiOpenedWindows[I][1] == N)
            {
                GuiMemoPaintOnePage(I, N, Page);
            }
        }
    }
}

