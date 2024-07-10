const StorageList_ctrl = document.getElementById("StorageList");
const StorageMemoCode_ctrl = document.getElementById("StorageMemoCode");
const StorageMemoMachine_ctrl = document.getElementById("StorageMemoMachine");
const StorageMemoMachineMem_ctrl = document.getElementById("StorageMemoMachineMem");
const StorageMemoSwapPage_ctrl = document.getElementById("StorageMemoSwapPage");

const StoragePrefix = "SDCC_";

let LayoutConfInstrQuan = DataGetIDefault(StoragePrefix + "LayoutConfInstrQuan", 1000000);


let DebugMode = false;
let GuiGraphRepaintPeriod = DataGetIDefault(StoragePrefix + "LayoutConfGraphPeriod", 500);

let LayoutConfWidgetFontSize = DataGetIDefault(StoragePrefix + "LayoutConfWidgetFontSize", 12);
let LayoutConfGraphFontSize = DataGetIDefault(StoragePrefix + "LayoutConfGraphFontSize", 1);

let ProgLoaded = false;
let ProgInitialized = false;
let ProgStarted = false;
let ScriptRequestQueue = [];
let FontLoaded = false;

function ScriptRequestPush(Val)
{
    ScriptRequestQueue.push(Val);
}

function ScriptRequestPop()
{
    if (ScriptRequestQueue.length > 0)
    {
        let X = ScriptRequestQueue[0];
        ScriptRequestQueue.shift();
        return X;
    }
    return 0;
}

function ValueInt(Val)
{
    const ValX = parseInt(Val);
    if (isNaN(ValX))
    {
        return 0;
    }
    else
    {
        return ValX;
    }
}

function HexToNum4(X)
{
    let N = "0123456789ABCDEF0123456789abcdef".indexOf(X);
    if (N >= 16)
    {
        N -= 16;
    }
    if (N < 0)
    {
        return 0;
    }
    return N;
}

function HexToNum8(X)
{
    let N1 = HexToNum4(X[0]);
    let N2 = HexToNum4(X[1]);
    return (N1 << 4) + N2;
}

function HexToNum16(X)
{
    let N1 = HexToNum4(X[0]);
    let N2 = HexToNum4(X[1]);
    let N3 = HexToNum4(X[2]);
    let N4 = HexToNum4(X[3]);
    return (N1 << 12) + (N2 << 8) + (N3 << 4) + N4;
}

function HexToNum(X)
{
    let N = 0;
    for (let I = 0; I < X.length; I++)
    {
        N = N * 16;
        N = N + HexToNum4(X[I]);
    }
    return N;
}

function NumToHex4(X)
{
    return X.toString(16).toUpperCase().padStart(1, '0');
}

function NumToHex8(X)
{
    return X.toString(16).toUpperCase().padStart(2, '0');
}

function NumToHex16(X)
{
    return X.toString(16).toUpperCase().padStart(4, '0');
}

function StopwatchReset()
{
    StopwatchOffset = performance.now();
    Stopwatch = [];
}

function StopwatchTime()
{
    Stopwatch.push(performance.now() - StopwatchOffset);
}

function ASCII(CharVal, NonPrintable)
{
    if ((CharVal >= 32) && (CharVal <= 126))
    {
        return CharVal;
    }
    if (CharVal == 13)
    {
        return 10;
    }
    if (CharVal == 10)
    {
        return 10;
    }
    return NonPrintable;
}

function StringASCII(Str, NonPrintable, Type)
{
    if ((typeof NonPrintable) == "string")
    {
        NonPrintable = NonPrintable.charCodeAt(0);
    }
    let StrASCII = "";
    for (let I = 0; I < Str.length; I++)
    {
        StrASCII = StrASCII + String.fromCharCode(ASCII(Str.charCodeAt(I), NonPrintable));
    }
    return StrASCII;
}

function StringBufDecode(Str)
{
    let StrDec = "";
    let DecodeState = 0;
    let TempNum = 0;
    for (let I = 0; I < Str.length; I++)
    {
        switch (DecodeState)
        {
            case 0:
                if (Str[I] == '_')
                {
                    DecodeState = 1;
                    TempNum = 0;
                }
                else
                {
                    StrDec = StrDec + Str[I];
                }
                break;
            case 1:
                if (Str[I] == ',')
                {
                    DecodeState = 0;
                    StrDec = StrDec + String.fromCharCode(TempNum);
                }
                else
                {
                    TempNum = TempNum * 10;
                    TempNum = TempNum + Str.charCodeAt(I) - 48;
                }
                break;
        }
    }
    return StrDec;
}

function DataTextToBlob(Data)
{
    const DataStr = atob(Data);
    const DataNum = new Array(DataStr.length);
    for (let i = 0; i < DataStr.length; i++)
    {
        DataNum[i] = DataStr.charCodeAt(i);
    }
    return new Blob([new Uint8Array(DataNum)], {type: "application/octet-stream"});
}

function BrowserW()
{
    return window.innerWidth;
}

function BrowserH()
{
    return window.innerHeight;
}

function BrowserF()
{
    return window.devicePixelRatio;
}

function String_fromCharCode(T)
{
    if ((T <= 0xD7FF) || ((T >= 0xE000) && (T <= 0xFFFF)))
    {
        return String.fromCharCode(T);
    }
    else
    {
        T = T - 65536;
        var V1 = T >> 10;
        var V2 = T & 1023;
        return String.fromCharCode(V1 + 0xD800, V2 + 0xDC00);
    }
}

