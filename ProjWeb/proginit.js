function ProgInit()
{
    if (ProgLoaded)
    {
        _ProgInit = Module.cwrap("Init", null, ["string"]);
        _ProgCodeLoad = Module.cwrap("CodeLoad", null, ["number", "number", "number", "string", "string", "number"]);
        _ProgCodeStart = Module.cwrap("CodeStart", null, ["number"]);
        _ProgCodeStop = Module.cwrap("CodeStop", null, ["number", "number"]);
        _ProgCodeInt = Module.cwrap("CodeInt", null, ["number", "number", "number", "number"]);
        _ProgMemoMap = Module.cwrap("MemoMap", null, ["number", "number", "number"]);
        _ProgCodeReset = Module.cwrap("CodeReset", null, ["number", "number"]);
        _ProgWidgetRefresh = Module.cwrap("WidgetRefresh", null, ["number", "number"]);
        _ProgWidgetInvokeEvent = Module.cwrap("WidgetInvokeEvent", null, ["number", "number", "number", "string"]);
        _ProgGraphClearScreen = Module.cwrap("GraphClearScreen", null, ["number", "number", "number", "number"]);
        _ProgGraphRepaintScreen = Module.cwrap("GraphRepaintScreen", null, ["number", "number", "number", "number"]);
        _ProgGraphSetParams = Module.cwrap("GraphSetParams", null, ["number", "number", "number", "number", "number", "number", "number", "number", "number", "number", "number", "number", "number"]);
        _ProgGuiSetParams = Module.cwrap("GuiSetParams", null, null);
        _ProgInit("1");
    }
}




function WindowResize()
{
}
window.addEventListener("resize", WindowResize, false);


function goodbye(e)
{
    if (!DebugMode)
    {
        if(!e) e = window.event;
        //e.cancelBubble is supported by IE - this will kill the bubbling process.
        e.cancelBubble = true;
        e.returnValue = 'You sure you want to leave?'; //This is displayed on the dialog

        //e.stopPropagation works in Firefox.
        if (e.stopPropagation)
        {
            e.stopPropagation();
            e.preventDefault();
        }
    }
}
window.onbeforeunload = goodbye;

