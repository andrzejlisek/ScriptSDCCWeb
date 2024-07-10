# Script SDCC library/API

The **ScriptSDCC** provides own API, which allows to make input/output for scripts running inside the virtual engine\. The only input/output interface is specified memory page \(up to 256 bytes\) called **swap page**\. The code and data address range can not encompass the swap page or the script will not work correctly\. The I/O operations rlys on the first byte in **swap page**, which normally should be **00h**\. If the byte gets other value, the **ScriptSDCC** does operation assigned to the byte just after executing the instruction, which changed the byte and changest the byte back to **00h**\. The other bytes are user for data exchange between engine and user\.

The library contains many functions and function\-like macros, which substantially easies interaction between script engine and user\.

The library consists of several **\*\.h** files\. The examples of usage are described in **Readme\_examples\.md** file\.

# core\.h

The **core\.h** file id the first file, which must be included in every **ScriptSDCC** script program\. Other library files also uses functions from the **core\.h** file\. Apart from the functions, the file constains the constatns and some keywords, which unifies the script source code\.

The **core\.h** file refers to the **\_\.h** file, which contents is specified for scripts, especially the engine type and swap page address\.

The **core\.h** file contains the one\-word number type names with explicitly determined signed/unsigned\. The names are preceeded with the **s** for signed types and with **u** for unsigned types\. The all types are following:


* **uchar**, **schar**
* **ushort**, **sshort**
* **uint**, **sint**
* **ulong**, **slong**

The **float** type does not have the signed/unsigned variants, the **double** type is not supported by SDCC 4\.4\.0\.

Some functions in most header files has several variants, for each data type\. In this document, such functions are mentioned once with **\#** character in the name, which indicates the data type and should be replaced into one of the one\-word data type mentioned above or **float** type\. For instance, the **void func\_\#\(\# value\)** notation means the serie as following;


* **void func\_uchar\(uchar value\)**
* **void func\_schar\(schar value\)**
* **void func\_ushort\(ushort value\)**
* **void func\_sshort\(sshort value\)**
* **void func\_uint\(uint value\)**
* **void func\_sint\(sint value\)**
* **void func\_ulong\(ulong value\)**
* **void func\_slong\(slong value\)**
* **void func\_float\(float value\)**

In some cases, whet the function generates or process the string, for **char** data type, there are foru variants instead of two variants:


* **schar\_v** \- signed char treated as number value\.
* **uchar\_v** \- unsigned char treated as number value\.
* **schar\_t** \- signed char treated as one\-character text\.
* **uchar\_t** \- unsigned char treated as one\-character text\.

The **core\.h** file also allowes to use the **\_\_reentrant** key word even for compiling for **Z180** engine\. Originally, **SDCC** does not support the **\_\_reentrant** in Z180 and raises the compile error, so the **core\.h** library replaces this work into blank at preprocessor step\. The **\_\_reentrant** disables using the global memory space instead of stack when invoking function\. Normally, the **\_\_reentrant** is not necessary, but can cause malfunct recursive invokes\.

The library file unifies the interrupt routine implementation\. The function should be named as **\_\_interrupt1\(void\)** and **\_\_interrupt2\(void\)** for the first and second interrupt routine\. The macro contained in the **core\.h** file replaces the name into name appropriate for specified engine\.

There functions contained in this header are following:


* **void stop\(\)** \- Stop executing the script and wait for user resume or widget event\.
* **void end\(\)** \- Ends the script without resuming possibility\.
* **uchar engine\_number\(\)** \- Returns the number of engine, within the script is executed\.
* **ulong engine\_counter\(uchar div\)** \- Returns the current state of instruction counter\. The function can be user for measure the time of some operation\. The measurement is roughly, becauce this function also occupies several instructions\. The **div** parameter represents the divisor of returned value and counter reset:
  * **0** \- Reset counter and do not divide the value\.
  * **1** \- Reset counter and divide the value by 10\.
  * **2** \- Reset counter and divide the value by 100\.
  * \.\.\.
  * **18** \- Reset counter and divide the value by 10^18\.
  * **20** \- Do not reset counter and do not divide the value\.
  * **21** \- Do not reset counter and divide the value by 10\.
  * **22** \- Do not reset counter and divide the value by 100\.
  * \.\.\.
  * **38** \- Do not reset counter and divide the value by 10^18\.

The engine has internal string buffer, which allows to make string consisting of other string and number or read string as number\. For use the buffer, there are the following functions:


* **void string\_clear\(\)** \- Clear the buffer\.
* **void string\_set\(char \* V\)** \- Replace the buffer contents with the specified string\.
* **void string\_append\(char \* V\)** \- Append the string to the buffer\.
* **void string\_set\_\#\(\# V\)** \- Replace the buffer contents with the number as string\.
* **void string\_append\_\#\(\# V\)** \- Append the number as string to the buffer\.
* **ushort string\_get\(char \* V, ushort S\)** \- Read the buffer contents into the **V** pointer, the read characters will not me greater than **S** parameter\. The returned value id the current buffer length\. For measure buffer length, execute **ushort string\_get\(0, 255\)**, where **V** has null pointer and **S** has some value, surely exceeding the estimated buffer length\.
* **\# string\_get\_\#\(\)** \- Read the vhole buffer contents as the number of specified type\. If the buffer does not contain the number as strint, the function will return some garbage number\.

# console\.h

The general purpose of the header is writing the text to web browser console\. Normally, the script should not use the console for interact with user, you can use the console for write control and debugging messages\. The library has the following functions:


* **void console\_clear\(\)** \- Clear the buffer to be printed into console\. Execute this function before printing anything\.
* **void console\_string\(char \* V\)** \- Write string into console buffer\.
* **void console\_schar\_v\(schar V\)** \- Write number as string into console buffer\.
* **void console\_print\(\)** \- Sent the buffer contents into the web browser console\.

# widget\.h

The general input and output interface is the form containing widgets\. Using the widgets, you can control the script during working, an provide input data for computation performed by script\. The **ScriptSDCC** provides 16 forms, which can be used for user interface\. The widgets are placed into groups, when one group can contain other groups and widgets arranget horizontally or vertically\.

One form can contain up to 255 widgets including groups\. Every widget has numeric identifier and can be one of the following widgets:


* **Group** \- Can contain widgets or other groups\.
* **Button** \- Event can be raised by clicking the button\.
* **Switch** \- There is two\-state switch looking like checkbox\. Event can be raised by every clicking, during changing the switch state\.
* **Label** \- Event can not be raised and the widget is used for present static, non\-editable text\.
* **Text box** \- Event can be raised by changing the text\.
* **Slider** \- Event can be raised by moving the knob\.
* **Multiline box** \- Event can be raised by changing the text\.

The widget event can perform none, one or more of the the following:


* Run script or save form/widget identifiers\.
* Raise interrupt 1 only or raise interrupt 2 during script running\.
* Raise interrupt 2 only or raise interrupt 2 during script running\.

In every case of event, the form identifier and widget identifier after raising event will be available by **event\_form** and **event\_widget** variables, which are introduced by **widget\.h** library and are technically maps into two last bytes of **swap page**\.

The library contains the functions, most of them contains the **FormId** and **WidgetId** parameters, which are the form identifier and widget identifier\. The functions for the widget form management are following:


* **void widget\_clear\(uchar FormId\)** \- Clear the form by removing all widgets\.
* **void widget\_add\(uchar FormId, uchar WidgetId, uchar ParentWidgetId\)** \- Add new widget to the form\.
* **void widget\_remove\(uchar FormId, uchar WidgetId\)** \- Remove specified widget from the form and child widgets if the specified widget is a group\.
* **void widget\_set\_\#\(uchar FormId, uchar WidgetId, uchar Param, \# Value\)** \- Set the widget property as number, depending on **Param**:
  * **widget\_type** \- Set the widget type, just after adding widget, the type is **widget\_group**\. The possible widget types for use as **Value**\.
    * **widget\_group**
    * **widget\_label**
    * **widget\_button**
    * **widget\_switch**
    * **widget\_text**
    * **widget\_slider**
    * **widget\_multiline**
  * **widget\_size** \- Set the widget size in the percent\. Default widget size is 100\.
  * **widget\_event** \- Set the widget event by combining elementary event, for remove event, set as **0**\. There are available the following event types:
    * **widget\_interrupt1** \- Raise interrupt 1 only when script is stopped or raise interrupt 1 while script is running\.
    * **widget\_interrupt2** \- Raise interrupt 2 only when script is stopped or raise interrupt 2 while script is running\.
    * **widget\_runscript **\- Run script when script is stopped or reset, save form and widget identifiers when script is runnung\.
  * **widget\_event\_add** \- Add engine number, to which widget event will be raised\. By default, event is raised to the same engine, which added the widget\.
  * **widget\_event\_rem** \- Remove engine number, to which widget event will be raised\. By default, event is raised to the same engine, which added the widget\.
  * **widget\_value** \- Widget text or number value\.
  * **widget\_orientation** \- Widget orientation, work for **widget\_group** and **widget\_slider only**\. If the widget is **widget\_slider**, you have to set the orientation before setting the widget type\.
  * **widget\_min** \- Depends on widget type:
    * **widget\_label**, **widget\_button**, **widget\_text**, **widget\_multiline** \- Prepend additional text to the current widget value\.
    * **widget\_slider** \- Set the minimum possible value\.
  * **widget\_max** \- Depends on widget type:
    * **widget\_label**, **widget\_button**, **widget\_text**, **widget\_multiline** \- Append additional text to the current widget value\.
    * **widget\_slider** \- Set the maximum possible value\.
* **void widget\_set\_string\(uchar FormId, uchar WidgetId, uchar Param, char \* Value\)** \- Set the widget property as string, works the same way as **widget\_set\_\#**\. This function uses the string buffer described in **core\.h** chapter\. If the **Value** is NULL, then for string vale, will be used the string stored in the buffer already\.
* **\# widget\_get\_\#\(uchar FormId, uchar WidgetId, uchar Param\)** \- Get the widget property as number, the possible parameters as Param are the same as for **widget\_set\_\#**\.
* **ushort widget\_get\_string\(uchar FormId, uchar WidgetId, uchar Param, char \* Value, ushort ValueLen\)** \- Get the string value from the widget\. This function uses the string buffer described in the **core\.h** chapter and returns the length of string storen in the buffer like the **string\_get** function describet in the **core\.h** chapter\.
* **void widget\_raise\_event\(uchar FormId, uchar WidgetId\)** \- Raise event of the specified form and widget\. The result will be the same as invoking event by manually widget interaction in the current widget configuration\.

The other puspose of the widgets is the multithread scripts\. Every script can get or set the widget value and script can raise widget event, which runs or resumes script in another engine\. Every added widget, by default raises event to the same engine, which added the widget\. The engine can be changed by setting **widget\_event\_rem** and **widget\_event\_add** properties\. One widget can also raise event into several engines\.

# graph\.h

**ScriptSDCC** provides 16 graph canvases, on which you can paint simple dwo\-dimensional and three\-dimensional graphics\. The three\-dimensional graphics can be viewen in parallel projection with any factors for three data axis and can be limited in depth for view cross section\. The examples of various view capabilities are described in **Readme\_examples\.md** file\. Every canvas can have up to 255 threads for draw polyline\.

The library provides functions to draw any graphics, the first parameter is number of canvas:


* **void graph\_clear\(uchar CanvasId\)** \- Remove all graphics on the canvas and reset all threads\.
* **void graph\_thread\(uchar CanvasId, uchar Thr\)** \- Set the canvas thread for drawing polyline\. You can switch between thread when you drawing several polylines simultaneously\.
* **void graph\_thread\_reset\(uchar CanvasId\)** \- Reset the current thread, the new plotted point will not be a continuation of prvious polyline\.
* **void graph\_plot\_\#\(uchar CanvasId, \# X, \# Y, \# Z, uchar R, uchar G, uchar B\)** \- Plot the point in specified place in three dimensional space and having specified color in RGB model\.
* **void graph\_line\(uchar CanvasId, uchar Points\)** \- Convert last plotted point into line\.
* **void graph\_triangle\(uchar CanvasId\)** \- Convert three last plotted points into triangular surface\.

# graphtext\.h

This library extends graph capabilitied with placing text labels and other informations\. The text placement is also based on the points in three dimensional space, but the text is positioned after projection points to the screen\. The text uses monospace font with some Unicode characters\. For use these characters, you have to write the characters in UTF\-8 encoding\.

The library contains following functions:


* **void graph\_text\_color\(uchar CanvasId, uchar DispBackFore, uchar ColorBackR, uchar ColorBackG, uchar ColorBackB, uchar ColorForeR, uchar ColorForeG, uchar ColorForeB\)** \- Set the text background and foreground colors in RGB color model\. The DispBackFore has the following possible values:
  * **0** \- Transparent backgrount and foreground, text will be invisible
  * **1** \- Transparent backgrount and opaque foreground, character will be visible
  * **2** \- Opaque backgrount and transparent foreground, rectangle with character\-shaped holes will be rendered\.
  * **3** \- Opaque backgrount and foreground, the text will be rendered on the rectangular background\.
* **void graph\_text\_color\_f\(CanvasId, uchar R, uchar G, uchar B\)** \- Equivalent of **graph\_text\_color\(CanvasId, 1, 0, 0, 0, R, G, B\)**, sets the foreground color only\.
* **void graph\_text\_color\_b\(CanvasId, uchar R, uchar G, uchar B\)** \- Equivalent of **graph\_text\_color\(CanvasId, 2, R, G, B, 0, 0, 0\)**, sets the background color only\.
* **void graph\_text\_xyz\_\#\(uchar CanvasId, \# X, \# Y, \# Z\)** \- Set the coordinates of text base point\.
* **void graph\_text\_\#\(uchar CanvasId, \# V\)** \- Render the number\. The schar and uchar number can be rendered as number or as sungle character\.
* **void graph\_text\_string\(uchar CanvasId, char \* V\)** \- Renders specified text string\.
* **void graph\_text\_move\(uchar CanvasId, short X, short Y, uchar Mode\)** \- Moves the render point on the display screen against the base point in halves of character width/height\. This function allows to render multiline text based on single point\. There are two modes of movement:
  * **0** \- Absolute position, related to base point\.
  * **1** \- Relative position, related to last offset\.

# mathx\.h

There is the library designed for mathematical operations and intriduces some mathematical constants\. Some of them hast the **\_** character \(underscore\) for avoid the name collision with the constatn/function contained in standard **math\.h** library\.

The basic constants and functions are folowing:


* **M\_E\_** \- Value of e constant\.
* **M\_PI\_** \- Value of pi constant\.
* **angle\_deg\_rad** \- Value of pi/180, used for convert angle from degrees to radians\.
* **angle\_rad\_deg** \- Value of 180/pi, used for convert angle from radians to degrees\.
* **\# abs\_\(\# X\)** \- Absolute value of number\.
* **\# equal\_\(\# A, \# B, \# T\)** \- Check the equalness of **A** and **B** with tollerance **T** and returns one of the following values:
  * **1** \- Difference between A and B are within the tolerance\.
  * **0** \- Difference between A and B are greater than the tolerance\.
* **float roundf\_\(float V\)** \- Round the value into nearest integer number\.

Some mathematical operations implemented on 8\-bit processor consumes a lot of instructions and takes quite long time\. For avoid this, the mathx\.h provides the functions, which computer the four basic operations:


* **\# engine\_add\_\#\(\# Arg1, \# Arg2\)** \- Addition of numbers
* **\# engine\_sub\_\#\(\# Arg1, \# Arg2\)** \- Subtraction of numbers
* **\# engine\_mul\_\#\(\# Arg1, \# Arg2\)** \- Multiplication of numbers
* **\# engine\_div\_\#\(\# Arg1, \# Arg2\)** \- Division of numbers

Additionally, the **mathx\.h** provides the functions for float numbers, that performs exactly the same operation as the same equivalent from the **math\.h** library, so the description of the functions is not necessary\. In the notation, the only difference is the **engine\_** prefix:


* **float engine\_roundf\(float Arg\)**
* **float engine\_floorf\(float Arg\)**
* **float engine\_ceilf\(float Arg\)**
* **float engine\_truncf\(float Arg\)**
* **float engine\_cosf\(float Arg\)**
* **float engine\_sinf\(float Arg\)**
* **float engine\_tanf\(float Arg\)**
* **float engine\_acosf\(float Arg\)**
* **float engine\_asinf\(float Arg\)**
* **float engine\_atanf\(float Arg\)**
* **float engine\_atan2f\(float Arg1, float Arg2\)**
* **float engine\_expm1f\(float Arg\)**
* **float engine\_log1pf\(float Arg\)**
* **float engine\_coshf\(float Arg\)**
* **float engine\_sinhf\(float Arg\)**
* **float engine\_tanhf\(float Arg\)**
* **float engine\_acoshf\(float Arg\)**
* **float engine\_asinhf\(float Arg\)**
* **float engine\_atanhf\(float Arg\)**
* **float engine\_erff\(float Arg\)**
* **float engine\_erfcf\(float Arg\)**
* **float engine\_tgammaf\(float Arg\)**
* **float engine\_lgammaf\(float Arg\)**
* **float engine\_logf\(float Arg\)**
* **float engine\_log10f\(float Arg\)**
* **float engine\_log2f\(float Arg\)**
* **float engine\_expf\(float Arg\)**
* **float engine\_exp2f\(float Arg\)**
* **float engine\_powf\(float Arg1, float Arg2\)**
* **float engine\_sqrtf\(float Arg\)**
* **float engine\_cbrtf\(float Arg\)**
* **float engine\_hypotf\(float Arg1, float Arg2\)**

# random\.h

The library provides the pseudo\-random numbers\. Its contains the only one serie of functions:


* **\# random\_get\_\#\(\# Min, \# Max\)** \- Get the random number between the **Min** and **Max** value\. For simulate rolling the standard cube dice into unsigned character value, execute the **random\_get\_uchar\(1, 6\)**\.

Every engine has own instance of pseudo\-random number generator initialized by wallclock time at the engine creation\.

# memo\.h

**ScriptSDCC** provided 256 shared memory spaces and 256 local memory spaces per engine\. The memory spaces allows to manipulate on data occupying much more memory, than 64kB reduced by code memory\. The memoriy is organized as array of numbers and the capacity is not limited\. You should not confuse several types in the same memory\.

The local memory has shorter access time than the shared memory, but the shared memory is needed if you want to access to the same memory from several engines\.

By default, memory space from 0 to 127 are the local, and the spaced from 128 to 255 are the shared\.

For manage the arraries, the **memo\.h** contains the following functions:


* **void memo\_local\_shared\(uchar N\)** \- Set the number threshold of local and shared memories, the number up to **N** will access to shared memory, the number above **N** will access to local memory\.
* **void memo\_shared\_local\(uchar N\)** \- Set the number threshold of shared and local memories, the number up to **N** will access to local memory, the number above **N** will access to shared memory\.
* **void memo\_clear\(uchar N\)** \- Clear the memory\.
* **\# memo\_get\_schar\(uchar N, slong Pos\)** \- Read the value at the specified position\. If the value is not written, the function will return **0**\.
* **void memo\_set\_schar\(uchar N, slong Pos, \# Val\)** \- Write the value at the specified position\.

# Num

The library consists of the 8 header files and it can be used in other software to use big numbers\.

The library are the files mentioned below, for almost each file there are listed methods intended to use outside this library\.

## Big number variable

To declare big number variable, there are two macros, internally, the number variable is an array of certain unsigned integer type:


* **numDef\(variable\)** \- big number variable\.
* **numPtr\(variable\)** \- pointer to big number variable\.

## numdef\.h

Parameter value definition\. This is configuration file, where programmer can affect the featuses such as the maximum number value, the variable types, which are used etc\.

## numcore\.h

The main core file:


* **void numInit\(\)** \- Core initialization \- it must be performed before any operation, once in whole program\.
* **void numZero\(numPtr\(N\)\)** \- Set 0 as number value\.
* **void numCopy\(numPtr\(NI\), numPtr\(NO\)\)** \- Copy number value from NI to NO\.
* **void numSignSet\(numPtr\(N\), numByte S\)** \- Set the number value sign \(0 \- positive, 1 \- negative\)\.
* **numByte numSignGet\(numPtr\(N\)\)** \- Get the number value sign\.
* **numSignGetAbs\(numPtr\(N\)\)** \- Get the number value sign and remove sign \(convert to absolute value\)\.
* **numSignGetInv\(numPtr\(N\)**\) \- Get the number value sign and invert sign\.

## numbase\.h

The base number operations:


* **numByte numCompare\(numPtr\(N1\), numPtr\(N2\)\)** \- Number compare \(N1<N2 ==> \-1; N1=N2 ==> 0; N1>N2 ==> 1\)\.
* **void numAdd\(numPtr\(N1\), numPtr\(N2\), numPtr\(N3\)\)** \- Number add \(N3=N1\+N2\)\.
* **void numSub\(numPtr\(N1\), numPtr\(N2\), numPtr\(N3\)\)** \- Number subtract \(N3=N1\-N2\)\.
* **void numMul\(numPtr\(N1\), numPtr\(N2\), numPtr\(N3\)\)** \- Num multiply \(N3=N1\*N2\)\.
* **void numDiv\(numPtr\(N1\), numPtr\(N2\), numPtr\(N3\)\)** \- Num divide \(N3=N1/N2\), division be 0 returns the minimum possible number value or the maximum possible number value depending on dividend sign\.

## numio\.h

Convert between number value and text to input or output number value:


* **void numSet\(numPtr\(N\), numChar \* Val\)** \- Set number value based on text\.
* **void numGet\(numPtr\(N\), numChar \* Val\)** \- Print number value as text\.
* **void numSetArray\(numPtr\(N\), numElementType \* NumA, numElementType Weight, numIOArrayIterator ElementCount\)** \- Set number value based on array\.
* **numByte numGetArray\(numPtr\(N\), numElementType \* NumA, numElementType Weight, numIOArrayIterator Count\)** \- Read number sign and absolute value into array\.

## numtaylor\.h

Functions using Taylor series:


* **void numInitTaylor\(\)** \- Structure initialization \- it must be performed before any operation using Taylor serie, once in whole program\.
* **void numSin\(numPtr\(Arg\), numPtr\(Val\)\)** \- Sine \(Val=sin\(Arg\)\)\.
* **void numCos\(numPtr\(Arg\), numPtr\(Val\)\)** \- Cosine \(Val=cos\(Arg\)\)\.
* **void numTan\(numPtr\(Arg\), numPtr\(Val\)\)** \- Tangent \(Val=tan\(Arg\)=sin\(Arg\)/cos\(Arg\)\)\.
* **void numCot\(numPtr\(Arg\), numPtr\(Val\)\)** \- Cotangent \(Val=cot\(Arg\)=cos\(Arg\)/sin\(Arg\)\)\.
* **void numSec\(numPtr\(Arg\), numPtr\(Val\)\)** \- Secant \(Val=sec\(Arg\)=1/cos\(Arg\)\)\.
* **void numCsc\(numPtr\(Arg\), numPtr\(Val\)\)** \- Cosecant \(Val=csc\(Arg\)=1/sin\(Arg\)\)\.

## numround\.h

Rounding numbers and multiply/divide by multiply of 10:


* **void numMul10\(numPtr\(N\), numIteratorSignedType I\)** \- Multiply number by 10^I \(I > 0\)\.
* **void numDiv10\(numPtr\(N\), numIteratorSignedType I\)** \- Divide number by 10^I \(I > 0\)\.
* **void numRound\(numPtr\(N\), numIteratorSignedType I, numByte Corr\)** \- Round number\.

## nummath\.h

Other mathematical functions:


* **void numExp\(numPtr\(X\), numPtr\(N\), numPtr\(Val\)\)** \- Power of integer exponent \(Val=X^N\)\.
* **void numRoot\(numPtr\(X\), numPtr\(N\), numPtr\(Val\)\)** \- Root of integer degree other than 0 \(Val^N=X\)\.

## numdebug\.h

Functions usable in testing and debugging this library:


* **void numGetRaw\(numPtr\(N\), numByte NoSplit, numChar \* Val\)** \- Print number raw value\.
* **void numSetBits\(numPtr\(N\), numChar \* Val\)** \- Set number value based on bit sequence\.



 

