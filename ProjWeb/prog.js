let _ProgInit;
let _ProgCodeLoad;
let _ProgCodeReset;
let _ProgCodeStart;
let _ProgCodeStop;
let _ProgCodeInt;
let _ProgMemoMap;
let _ProgWidgetRefresh;
let _ProgWidgetInvokeEvent;
let _ProgGraphClearScreen;
let _ProgGraphRepaintScreen;
let _ProgGraphSetParams;
let _ProgGuiSetParams;

function ProgGuiSetParamsX()
{
    if (FontLoaded)
    {
        _ProgGuiSetParams();
    }
}

function ProgStart()
{
    if (FontLoaded)
    {
        ProgGuiSetParamsX();
        ProgStarted = true;
        
        const ProgInitScreenObj = document.getElementById("InitScreen");
        ProgInitScreenObj.style.display = "none";
        ProgInitScreenObj.innerHTML = "";
        GuiGraphRepaintAllTimer();
    }
    else
    {
        setTimeout(ProgStart, 100);
    }
}


function _ProgCallback(D)
{
    switch (D[0])
    {
        case 100: // Init
            ProgStart();
            break;
        case 101: // CodeLoad|CodeReset
            if (parseInt(D[2]) > 0)
            {
                StorageMemo[D[1]].CodeExists = true;
            }
            else
            {
                StorageMemo[D[1]].CodeExists = false;
            }
            StorageMemo[D[1]].Entry = D[3];
            StorageMemo[D[1]].StatusC = 0;
            StorageMemoCode = [];
            for (let I = 0; I < 256; I++)
            {
                if (StorageMemo[I].CodeExists)
                {
                    StorageMemoCode.push(I);
                }
            }
            LayoutStatusInfoRefresh();
            break;
        case 102: // CodeRun|CodeInt
            TimingSet(D[1], D[2]);
            StorageMemo[D[1]].StatusC = D[3];
            switch (StorageMemo[D[1]].StatusC)
            {
                case 0:
                    GuiGraphRepaintAll();
                    StorageMemo[D[1]].Running = true;
                    break;
                case 1:
                case 2:
                case 3:
                case 8:
                    GuiGraphRepaintAll();
                    TimingReset(D[1]);
                    StorageMemo[parseInt(D[1])].Running = false;
                    GuiGraphRepaintAllTimer();
                    break;
            }
            LayoutStatusInfoRefresh();
            break;
    }
}

      var Module = {
        print: (function() {
          return function(text) {
            if (arguments.length > 1) text = Array.prototype.slice.call(arguments).join(' ');
            // These replacements are necessary if you render to raw HTML
            //text = text.replace(/&/g, "&amp;");
            //text = text.replace(/</g, "&lt;");
            //text = text.replace(/>/g, "&gt;");
            //text = text.replace('\n', '<br>', 'g');
            console.log(text);
          };
        })(),
        canvas: (() => {
          var canvas = document.getElementById('canvas');

          // As a default initial behavior, pop up an alert when webgl context is lost. To make your
          // application robust, you may want to override this behavior before shipping!
          // See http://www.khronos.org/registry/webgl/specs/latest/1.0/#5.15.2
          //canvas.addEventListener("webglcontextlost", (e) => { alert('WebGL context lost. You will need to reload the page.'); e.preventDefault(); }, false);

          return canvas;
        })(),
        setStatus: (text) => {
          if (!Module.setStatus.last) Module.setStatus.last = { time: Date.now(), text: '' };
          if (text === Module.setStatus.last.text) return;
          var m = text.match(/([^(]+)\((\d+(\.\d+)?)\/(\d+)\)/);
          var now = Date.now();
          if (m && now - Module.setStatus.last.time < 30) return; // if this is a progress update, skip it if too soon
          Module.setStatus.last.time = now;
          Module.setStatus.last.text = text;
          if (m) {
            text = m[1];
            //progressElement.value = parseInt(m[2])*100;
            //progressElement.max = parseInt(m[4])*100;
            //progressElement.hidden = false;
            //spinnerElement.hidden = false;
          } else {
            //progressElement.value = null;
            //progressElement.max = null;
            //progressElement.hidden = true;
            //if (!text) spinnerElement.style.display = 'none';
          }
          //console.log("Status: " + text);
          
          if (text == "")
          {
            ProgLoaded = true;
            ProgInit();
          }
        },
        totalDependencies: 0,
        monitorRunDependencies: (left) => {
          this.totalDependencies = Math.max(this.totalDependencies, left);
          Module.setStatus(left ? 'Preparing... (' + (this.totalDependencies-left) + '/' + this.totalDependencies + ')' : 'All downloads complete.');
        }
      };
      Module.setStatus('Downloading...');
      window.onerror = (event) => {
        // TODO: do not warn on ok events like simulating an infinite loop or exitStatus
        Module.setStatus('Exception thrown, see JavaScript console');
        //spinnerElement.style.display = 'none';
        Module.setStatus = (text) => {
          if (text) console.error('[post-exception status] ' + text);
        };
      };



