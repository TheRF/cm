# cm

A small tool that relocates files to a given location while also creating a backup on another location.


cm = copy+move

## Requirements

- a C++17 compliant compiler (filesystem)

## Building

Simply running make creates an executable *cm*. Simply copy that file wherever you want.

## Caution

As this is a rudimentary implementation it will not take into account whether a file with the same name already exists in the target location. If a file already exists the process will fail right there.

## Usage

>cm ((config flag)( (file))+)+


Note: wildcards are not supported!

## Configuration

cm doesn't come with prebuild flags. Instead flags are defined in the config file *.cm* located in the HOME directory.

The configuration file is built as follows:

>(root of copy location)  
>(root of move location)  
>(flag definition 2)  
>(flag definition 1)  
>...

A flag definition is build as follows:

>(flag);(copy relative path);(move relative path)

## Example for a configuration file

>/home/user/
>/run/media/user/backup
>-doc;docs/;docs/
>-pic;pictures/;public/pictures/

## Example using the configuration file

>cm -doc document1.pdf document2.odt
