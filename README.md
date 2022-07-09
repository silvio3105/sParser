# sParser

## ABOUT

This library contains functions for parsing C string. The library doesn't use dynamic memory allocation. 
Supported format is(in case for parsing commands): `cmd1,param1,...,paramN;...;cmdN,...,paramN;` where `;` is delimiter 1, and `,` is delimiter 2.
See example sketches for better understanding of the library. Library is not framework depended.

<br/><br/>

## INSTALLATION

<ul>
  <li>Download the library</li>
  <li>Extract files using WinRAR(or similar software) to location <i>C:\Users\{YOUR_USERNAME}\Documents\Arduino\libraries</i> or project folder.</li>
</ul>

<br/><br/>

## USING LIBRARY

In your sketch, at the top add `#include <sParser.h>`. Somewhere below all include files, add `sParser {OBJECT_NAME}({DELIMITER_1},{DELIMITER_2});`
Recommended delimiters are `;` and `,`.

<br/><br/>

## SETTINGS

There is no settings you can adjust.

<br/><br/>

## FUNCTIONS

### char *find(const char *input, uint8_t const type)

Finds string set in given C string.

<b>Parameters</b>
<ul>
  <li><b>*input</b> - Memory address of first character. C string has to be NULL terminated.</li>
  <li><b>type</b> - Selects delimiter</li>
</ul>

<b>Return</b>
<ul>
  <li>Address of first character</li>
</ul>

<br/>

### uint8_t count(const char *input, uint8_t const type)

Counts number of string sets in given C string.

<b>Parameters</b>
<ul>
  <li><b>*input</b> (optional) - Memory address of first character. C string has to be NULL terminated.
If not provided, function will use <i>next</i> memory address for selected <i>type</i>.</li>
  <li><b>type</b> - Selects delimiter.</li>
</ul>

<b>Return</b>
<ul>
  <li>Number of string sets</li>
</ul>

<br/>

### char *getNext(uint8_t const type)

Returns memory address of next string set.

<b>Parameters</b>
<ul>
  <li><b>type</b> - Selects delimiter.</li>
</ul>

<b>Return</b>
<ul>
  <li>Memory of <i>next</i> selected <i>type</i></li>
</ul>

<br/>

### char *getNext(uint8_t const type)

Returns memory address of last string set found in `find` function.

<b>Parameters</b>
<ul>
  <li><b>type</b> - Selects delimiter</li>
</ul>

<b>Return</b>
<ul>
  <li>Memory of <i>last</i> selected <i>type</i></li>
</ul>

<br/><br/>

## KNOWN ISSUES

There is no known issues. If you find issue, open new issue at Github.
