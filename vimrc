
if has('filetype')
	filetype indent plugin on
endif

if has('syntax')
	syntax on
endif

set wildmenu
set showcmd

set backspace=indent,eol,start

filetype plugin indent on
" On pressing tab, insert 2 spaces
set expandtab
" show existing tab with 2 spaces width
set tabstop=2
set softtabstop=2
" when indenting with '>', use 2 spaces width
set shiftwidth=2

" set autoindent
set cindent
set cinkeys-=0#
set indentkeys-=0#

set nostartofline

set number

set tabstop=4
