# Stratus

## About
Stratus is a markup language, created to be convertable to HTML/CSS, and have
a more "programming" vibe to it (despite functionally being quite similar to 
HTML/CSS). This repo converts Stratus files (ending in .str) to HTML/CSS files,
operating as a Static Site Generator.

## Installation
Download Mingw64 onto your device, and clone this repo in order to use Stratus.
### Writing Stratus Files
Stratus files are divided into two portions (much like HTML/CSS files). The
**Head** and the **Body**.
#### Head
The first part of the stratus file is called the **head**. The head contains the
title of the website, as well as all of the imports.

**To give your webpage a title:**
`TITLE=My title`

**To import other files:**
```
IMPORT{
    cssFile.css
    component.str AS myCmponent
 }
```
The `AS` keyword names the component (ie what you use it as). Not including
this means that the component will default to being called whatever the name
of the file is, without the file ending. (`component.str` -> `component`)

#### Body
Put the keyword `BODY` at the top of your body to indicate that the body
portion is beginning. Stratus essentially follows HTML/CSS element names (h1,
div, p, a, etc). However, the elements instead should be formatted as follows:
```
_div(attributes here){
    _p(class="text"){
        This is some text
    }
}
```
Thus all HTML type keywords should begin with an underscore (`_`).
\n
To include components you created, use two underscores instead of
one. To add in any necessary parameters, place them in the parenthesis.
Using your own components doesn't require any brackets (`{}`).
```
__myComponent(param="cat")
```

In order to create a parameterized component, in the HEAD of the 
project, include a `PARAMETERS` section. The only two data types accepted for parameters are FILE and STRING.
STRING will simply take all instances of that parameter and use the
string passed in, while FILE will take all usages of that parameter
and read in the file instead.

In order to use a parameter, simply put the parameter in braces:

```
PARAMETERS {
    STRING title,
    FILE file
}

BODY
_h1(){
    [title]
}
_p(){
    [file]
}
```


*For an example Stratus file, see the `input` folder of this repo* 

### Generating HTML/CSS From Stratus Files
1. Run `make compile` on your machine
2. Create a text file with all of the files you want converted to HTML/CSS on it
   - Note: Only include the files you want to be websites in this list. Any components
     may simply be imported and it should work fine
3. Execute `./build/stratus.exe [files to convert] [input filepath] [output filepath]` in the terminal
   - The files to convert should just be a text file containing the names
     (from the input-directory level) of the files to convert
   - The input filepath should be the filepath to the directory your Stratus and
     CSS files are stored in (with the `/` at the end)
   - The output filepath should be the directory you want all of the statically
     generated HTML files in (with the `/` at the end)
   - *For an example run command, see `makefile`, and for an example input text
     list, see `siteMake.txt`*
4. All of your HTML files should now be placed in the output folder
   - If there are any errors in your Stratus or CSS files, these may not be
     caught or error handled properly

## To Do
- Create more helpful error handling + terminal statements
- Figure out syntax highlighting for Stratus files
- Create library of helpful templates
- Making templates easier to create + use would be good too
- Include * and **, and other inline emphasizers (and \)
- Figure out embedding JavaScript
- Update stuff so it's no longer so line break dependent
- Create thing to loop through created files and put them all in
- Parse markdown files? (like for blog)

## Misc Grammar Notes
is element necessary data type if it could just be collapsed
into file?
