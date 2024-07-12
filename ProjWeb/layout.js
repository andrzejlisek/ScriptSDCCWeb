let LayoutValuesRow = [1, 2, 4];
let LayoutValuesCol = [16, 8, 4];

let LayoutButtonHeight = DataGetIDefault(StoragePrefix + "LayoutConfBtnHeight", 30);
let LayoutCols = LayoutValuesCol[DataGetIDefault(StoragePrefix + "LayoutConfRowsCols", 1)];
let LayoutRows = LayoutValuesRow[DataGetIDefault(StoragePrefix + "LayoutConfRowsCols", 1)];

const LayoutTableScript = document.getElementById("TableScript");
const LayoutTableWidget = document.getElementById("TableWidget");
const LayoutTableGraphi = document.getElementById("TableGraphi");

let LayoutOffsetScript = 0;
let LayoutOffsetWidget = 0;
let LayoutOffsetGraphi = 0;

let LayoutScriptSelected = 0;

let LayoutStatusInfo;

function LayoutLoadConf()
{
    document.getElementById("LayoutConfRowsCols").selectedIndex = DataGetIDefault(StoragePrefix + "LayoutConfRowsCols", 1);
    document.getElementById("LayoutConfBtnHeight").value = DataGetIDefault(StoragePrefix + "LayoutConfBtnHeight", 30);
    document.getElementById("LayoutConfInstrQuan").value = LayoutConfInstrQuan / 1000;
    document.getElementById("LayoutConfGraphPeriod").value = DataGetIDefault(StoragePrefix + "LayoutConfGraphPeriod", 500);
    document.getElementById("LayoutConfWidgetFontSize").value = DataGetIDefault(StoragePrefix + "LayoutConfWidgetFontSize", 12);
    document.getElementById("LayoutConfGraphPixelSize").value = DataGetIDefault(StoragePrefix + "LayoutConfGraphPixelSize", 1);
    document.getElementById("LayoutConfGraphFontSize").value = DataGetIDefault(StoragePrefix + "LayoutConfGraphFontSize", 1);
}


function LayoutSaveConf()
{
    DataSet(StoragePrefix + "LayoutConfRowsCols", document.getElementById("LayoutConfRowsCols").selectedIndex);
    DataSet(StoragePrefix + "LayoutConfBtnHeight", document.getElementById("LayoutConfBtnHeight").value);
    DataSet(StoragePrefix + "LayoutConfInstrQuan", parseInt(document.getElementById("LayoutConfInstrQuan").value) * 1000);
    DataSet(StoragePrefix + "LayoutConfGraphPeriod", document.getElementById("LayoutConfGraphPeriod").value);
    DataSet(StoragePrefix + "LayoutConfWidgetFontSize", document.getElementById("LayoutConfWidgetFontSize").value);
    DataSet(StoragePrefix + "LayoutConfGraphPixelSize", document.getElementById("LayoutConfGraphPixelSize").value);
    DataSet(StoragePrefix + "LayoutConfGraphFontSize", document.getElementById("LayoutConfGraphFontSize").value);
    
    LayoutConfInstrQuan = parseInt(document.getElementById("LayoutConfInstrQuan").value) * 1000;
    GuiGraphRepaintPeriod = parseInt(document.getElementById("LayoutConfGraphPeriod").value);
    LayoutConfWidgetFontSize = parseInt(document.getElementById("LayoutConfWidgetFontSize").value);
    LayoutConfGraphPixelSize = parseInt(document.getElementById("LayoutConfGraphPixelSize").value);
    LayoutConfGraphFontSize = parseInt(document.getElementById("LayoutConfGraphFontSize").value);
    LayoutButtonHeight = parseInt(document.getElementById("LayoutConfBtnHeight").value);
    ProgGuiSetParamsX();
}


function LayoutStatusInfoRefresh()
{
    if (LayoutStatusInfo)
    {
        let Msg = "";
        for (let I = 0; I < StorageMemoCode.length; I++)
        {
            Msg = Msg + StorageMemoCode[I] + ": ";
            if (StorageMemo[StorageMemoCode[I]].Running)
            {
                Msg = Msg + StorageMemo[StorageMemoCode[I]].TimingVal;
            }
            else
            {
                switch (StorageMemo[StorageMemoCode[I]].StatusC)
                {
                    case 0: Msg = Msg + "Reset"; break;
                    case 8: Msg = Msg + "Reset"; break;
                    case 1: Msg = Msg + "Stop"; break;
                    case 2: Msg = Msg + "End"; break;
                    case 3: Msg = Msg + "Error: " + StorageMemo[StorageMemoCode[I]].ErrorMsg; break;
                    case 9: Msg = Msg + "Gui"; break;
                }
            }
            Msg = Msg + "<br>";
        }
        LayoutStatusInfo.innerHTML = Msg;
    }
}


function LayoutBtnClick(Tbl, Idx)
{
    alert(Tbl, Idx);
}

function LayoutSetCaptions(Prefix, Offset)
{
    for (let I = 0; I < (LayoutRows * LayoutCols); I++)
    {
        //let N = NumToHex8(I + Offset);
        let N = (I + Offset);
        if (Prefix == "BtnScript")
        {
            if ((I + Offset) == LayoutScriptSelected)
            {
                N = "[" + N + "]";
            }
        }
        document.getElementById(Prefix + NumToHex8(I)).value = N;
    }
}

function LayoutButtonEventScript(N)
{
    LayoutScriptSelected = N;
    LayoutSetCaptions("BtnScript", LayoutOffsetScript);
}

function LayoutButtonEvent(Evt)
{
    Evt = Evt || window.event;
    const EvtSender = Evt.target || Evt.srcElement;
    const BtnId = EvtSender.id;
    const T = (LayoutCols * LayoutRows);

    switch (BtnId)
    {
        case "BtnScriptPrev": if (LayoutOffsetScript > 0)         LayoutOffsetScript -= (T); LayoutSetCaptions("BtnScript", LayoutOffsetScript); break;
        case "BtnScriptNext": if (LayoutOffsetScript < (256 - T)) LayoutOffsetScript += (T); LayoutSetCaptions("BtnScript", LayoutOffsetScript); break;
        case "BtnWidgetPrev": if (LayoutOffsetWidget > 0)         LayoutOffsetWidget -= (T); LayoutSetCaptions("BtnWidget", LayoutOffsetWidget); break;
        case "BtnWidgetNext": if (LayoutOffsetWidget < (256 - T)) LayoutOffsetWidget += (T); LayoutSetCaptions("BtnWidget", LayoutOffsetWidget); break;
        case "BtnGraphiPrev": if (LayoutOffsetGraphi > 0)         LayoutOffsetGraphi -= (T); LayoutSetCaptions("BtnGraphi", LayoutOffsetGraphi); break;
        case "BtnGraphiNext": if (LayoutOffsetGraphi < (256 - T)) LayoutOffsetGraphi += (T); LayoutSetCaptions("BtnGraphi", LayoutOffsetGraphi); break;


        case "BtnScriptMemoLoad": MemoLoad(LayoutScriptSelected); break;
        case "BtnScriptMemoReset": MemoResetBtn(LayoutScriptSelected); break;
        case "BtnScriptMemoStart": MemoStartBtn(LayoutScriptSelected); break;
        case "BtnScriptMemoStop": MemoStopBtn(LayoutScriptSelected); break;
        case "BtnScriptMemoDecompile": MemoDecompileBtn(LayoutScriptSelected); break;
        case "BtnScriptMemoPaint": MemoPaintBtn(LayoutScriptSelected); break;
    }
    for (let I = 0; I < T; I++)
    {
        if (BtnId == ("BtnScript" + NumToHex8(I))) { LayoutButtonEventScript(I + LayoutOffsetScript); }
        if (BtnId == ("BtnWidget" + NumToHex8(I))) { GuiOpenWidgets(I + LayoutOffsetWidget); }
        if (BtnId == ("BtnGraphi" + NumToHex8(I))) { GuiOpenGraph(I + LayoutOffsetGraphi); }
    }
}

function LayoutInitAddButton(Table, Row, Cell, Name)
{
    let Btn = document.createElement("input");
    Btn.type = "button";
    Btn.value = Name;
    Btn.style["width"] = "100%";
    Btn.style["height"] = LayoutButtonHeight + "px";
    Btn.setAttribute("id", Name);
    Btn.addEventListener("click", LayoutButtonEvent, false);
    Table.rows[Row].cells[Cell].appendChild(Btn);
}

function LayoutInit()
{
    LayoutLoadConf();
    
    let ButtonsPrevNext = 0;

    let CellPercent = [];
    switch (LayoutCols)
    {
        case 1: CellPercent = [100]; break;
        case 2: CellPercent = [50, 50]; break;
        case 4: CellPercent = [25, 25, 25, 25]; break;
        //case 8: CellPercent = [12, 13, 13, 12, 12, 13, 13, 12]; break;
        case 8: CellPercent = [12.5, 12.5, 12.5, 12.5, 12.5, 12.5, 12.5, 12.5]; break;
        //case 16: CellPercent = [6, 7, 6, 6, 6, 7, 6, 6, 6, 6, 7, 6, 6, 6, 7, 6]; break;
        case 16: CellPercent = [6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25, 6.25]; break;
        //case 32: CellPercent = [3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3, 3, 4, 3, 3, 3, 3, 3]; break;
    }
    
    LayoutTableScript.insertRow(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].cells[0].width = "50%";
    LayoutTableScript.rows[0].cells[0].colSpan = (LayoutCols * 2) / 4;
    LayoutTableScript.rows[0].cells[1].width = "25%";
    LayoutTableScript.rows[0].cells[1].colSpan = LayoutCols / 4;
    LayoutTableScript.rows[0].cells[2].width = "25%";
    LayoutTableScript.rows[0].cells[2].colSpan = LayoutCols / 4;
    LayoutTableScript.insertRow(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].insertCell(0);
    LayoutTableScript.rows[0].cells[0].width = "25%";
    LayoutTableScript.rows[0].cells[0].colSpan = LayoutCols / 4;
    LayoutTableScript.rows[0].cells[1].width = "25%";
    LayoutTableScript.rows[0].cells[1].colSpan = LayoutCols / 4;
    LayoutTableScript.rows[0].cells[2].width = "25%";
    LayoutTableScript.rows[0].cells[2].colSpan = LayoutCols / 4;
    LayoutTableScript.rows[0].cells[3].width = "25%";
    LayoutTableScript.rows[0].cells[3].colSpan = LayoutCols / 4;
    if (ButtonsPrevNext > 0)
    {
        LayoutTableScript.insertRow(0);
        LayoutTableScript.rows[0].insertCell(0);
        LayoutTableScript.rows[0].insertCell(0);
        LayoutTableScript.rows[0].cells[0].width = "50%";
        LayoutTableScript.rows[0].cells[0].colSpan = LayoutCols / 2;
        LayoutTableScript.rows[0].cells[1].width = "50%";
        LayoutTableScript.rows[0].cells[1].colSpan = LayoutCols / 2;
        LayoutTableWidget.insertRow(0);
        LayoutTableWidget.rows[0].insertCell(0);
        LayoutTableWidget.rows[0].insertCell(0);
        LayoutTableWidget.rows[0].cells[0].width = "50%";
        LayoutTableWidget.rows[0].cells[0].colSpan = LayoutCols / 2;
        LayoutTableWidget.rows[0].cells[1].width = "50%";
        LayoutTableWidget.rows[0].cells[1].colSpan = LayoutCols / 2;
        LayoutTableGraphi.insertRow(0);
        LayoutTableGraphi.rows[0].insertCell(0);
        LayoutTableGraphi.rows[0].insertCell(0);
        LayoutTableGraphi.rows[0].cells[0].width = "50%";
        LayoutTableGraphi.rows[0].cells[0].colSpan = LayoutCols / 2;
        LayoutTableGraphi.rows[0].cells[1].width = "50%";
        LayoutTableGraphi.rows[0].cells[1].colSpan = LayoutCols / 2;
    }

    for (let Y = 0; Y < LayoutRows; Y++)
    {
        LayoutTableScript.insertRow(0);
        LayoutTableWidget.insertRow(0);
        LayoutTableGraphi.insertRow(0);
        for (let X = 0; X < LayoutCols; X++)
        {
            LayoutTableScript.rows[0].insertCell(0);
            LayoutTableScript.rows[0].cells[0].width = CellPercent[X] + "%";
            LayoutTableWidget.rows[0].insertCell(0);
            LayoutTableWidget.rows[0].cells[0].width = CellPercent[X] + "%";
            LayoutTableGraphi.rows[0].insertCell(0);
            LayoutTableGraphi.rows[0].cells[0].width = CellPercent[X] + "%";
        }
    }

    let Idx = 0;
    for (let Y = 0; Y < LayoutRows; Y++)
    {
        for (let X = 0; X < LayoutCols; X++)
        {
            LayoutInitAddButton(LayoutTableScript, Y, X, "BtnScript" + NumToHex8(Idx));
            LayoutInitAddButton(LayoutTableWidget, Y, X, "BtnWidget" + NumToHex8(Idx));
            LayoutInitAddButton(LayoutTableGraphi, Y, X, "BtnGraphi" + NumToHex8(Idx));
            Idx++;
        }
    }
    
    if (ButtonsPrevNext > 0)
    {
        LayoutInitAddButton(LayoutTableScript, LayoutRows, 0, "BtnScriptPrev");
        LayoutInitAddButton(LayoutTableScript, LayoutRows, 1, "BtnScriptNext");
        LayoutInitAddButton(LayoutTableWidget, LayoutRows, 0, "BtnWidgetPrev");
        LayoutInitAddButton(LayoutTableWidget, LayoutRows, 1, "BtnWidgetNext");
        LayoutInitAddButton(LayoutTableGraphi, LayoutRows, 0, "BtnGraphiPrev");
        LayoutInitAddButton(LayoutTableGraphi, LayoutRows, 1, "BtnGraphiNext");

        document.getElementById("BtnScriptPrev").value = "Prev";
        document.getElementById("BtnWidgetPrev").value = "Prev";
        document.getElementById("BtnGraphiPrev").value = "Prev";
        document.getElementById("BtnScriptNext").value = "Next";
        document.getElementById("BtnWidgetNext").value = "Next";
        document.getElementById("BtnGraphiNext").value = "Next";
    }

    LayoutInitAddButton(LayoutTableScript, LayoutRows + ButtonsPrevNext, 0, "BtnScriptMemoLoad");
    LayoutInitAddButton(LayoutTableScript, LayoutRows + ButtonsPrevNext, 1, "BtnScriptMemoReset");
    LayoutInitAddButton(LayoutTableScript, LayoutRows + ButtonsPrevNext, 2, "BtnScriptMemoStart");
    LayoutInitAddButton(LayoutTableScript, LayoutRows + ButtonsPrevNext, 3, "BtnScriptMemoStop");
    LayoutInitAddButton(LayoutTableScript, LayoutRows + 1 + ButtonsPrevNext, 1, "BtnScriptMemoDecompile");
    LayoutInitAddButton(LayoutTableScript, LayoutRows + 1 + ButtonsPrevNext, 2, "BtnScriptMemoPaint");

    document.getElementById("BtnScriptMemoLoad").value = "Load";
    document.getElementById("BtnScriptMemoReset").value = "Reset";
    document.getElementById("BtnScriptMemoStart").value = "Start";
    document.getElementById("BtnScriptMemoStop").value = "Stop";
    document.getElementById("BtnScriptMemoDecompile").value = "Decompile";
    document.getElementById("BtnScriptMemoPaint").value = "Memory";

    LayoutStatusInfo = document.createElement("span");
    LayoutStatusInfo.innerHTML = "";
    LayoutTableScript.rows[LayoutRows + 1 + ButtonsPrevNext].cells[0].appendChild(LayoutStatusInfo);

    
    LayoutSetCaptions("BtnScript", 0);
    LayoutSetCaptions("BtnWidget", 0);
    LayoutSetCaptions("BtnGraphi", 0);


    document.getElementById("StorageList").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageButton1").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageButton2").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageButton3").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageButton4").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageButton5").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageMemoCode").style["height"] = (LayoutButtonHeight * 2) + "px";
    document.getElementById("StorageCodeBtn1").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageCodeBtn2").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageCodeBtn3").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageMemoMachine").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageMemoMachineMem").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("StorageMemoSwapPage").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfRowsCols").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfBtnHeight").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfInstrQuan").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfGraphPeriod").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfWidgetFontSize").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfGraphPixelSize").style["height"] = LayoutButtonHeight + "px";
    document.getElementById("LayoutConfGraphFontSize").style["height"] = LayoutButtonHeight + "px";

    LayoutStatusInfoRefresh();
}


LayoutInit();

