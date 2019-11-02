let SessionLoad = 1
if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
imap <Nul> <C-Space>
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <C-P> pumvisible() ? "\" : "\"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
inoremap <expr> <C-N> pumvisible() ? "\" : "\"
noremap! <Plug>SearchIndex <Nop>
inoremap <silent> <Plug>(ale_complete) :ALEComplete
inoremap <silent> <C-Tab> =UltiSnips#ListSnippets()
inoremap <silent> <Plug>NERDCommenterInsert  <BS>:call NERDComment('i', "insert")
inoremap <silent> <SNR>52_AutoPairsReturn =AutoPairsReturn()
imap <C-G>S <Plug>ISurround
imap <C-G>s <Plug>Isurround
imap <C-S> <Plug>Isurround
inoremap <silent> <Plug>(fzf-maps-i) :call fzf#vim#maps('i', 0)
inoremap <expr> <Plug>(fzf-complete-buffer-line) fzf#vim#complete#buffer_line()
inoremap <expr> <Plug>(fzf-complete-line) fzf#vim#complete#line()
inoremap <expr> <Plug>(fzf-complete-file-ag) fzf#vim#complete#path('ag -l -g ""')
inoremap <expr> <Plug>(fzf-complete-file) fzf#vim#complete#path("find . -path '*/\.*' -prune -o -type f -print -o -type l -print | sed 's:^..::'")
inoremap <expr> <Plug>(fzf-complete-path) fzf#vim#complete#path("find . -path '*/\.*' -prune -o -print | sed '1d;s:^..::'")
inoremap <expr> <Plug>(fzf-complete-word) fzf#vim#complete#word()
nnoremap d :Gdiff
nnoremap s :Gstatus
nnoremap ? :GFiles?
nnoremap p :GFiles
nnoremap b :Gblame
nnoremap c :BCommits
nnoremap l :BLines
nnoremap g :Ag
nnoremap t :Buffers
snoremap <silent>  c
xnoremap <silent> 	 :call UltiSnips#SaveLastVisualSelection()gvs
snoremap <silent> 	 :call UltiSnips#ExpandSnippet()
xnoremap <silent>  :call multiple_cursors#new("v", 0)
nnoremap <silent>  :call multiple_cursors#new("n", 1)
nnoremap  :Files
snoremap  "_c
nnoremap <silent>  p :call conque_gdb#print_word(expand("<cword>"))
nnoremap <silent>  f :call conque_gdb#command("finish")
nnoremap <silent>  s :call conque_gdb#command("step")
nnoremap <silent>  c :call conque_gdb#command("continue")
nnoremap <silent>  <S-Down> :BuffergatorMruCycleNext rightbelow sbuffer
nnoremap <silent>  <S-Right> :BuffergatorMruCycleNext rightbelow vert sbuffer
nnoremap <silent>  <S-Up> :BuffergatorMruCycleNext leftabove sbuffer
nnoremap <silent>  <S-Left> :BuffergatorMruCycleNext leftabove vert sbuffer
nnoremap <silent>  <Down> :BuffergatorMruCyclePrev rightbelow sbuffer
nnoremap <silent>  <Right> :BuffergatorMruCyclePrev rightbelow vert sbuffer
nnoremap <silent>  <Up> :BuffergatorMruCyclePrev leftabove sbuffer
nnoremap <silent>  <Left> :BuffergatorMruCyclePrev leftabove vert sbuffer
nnoremap <silent>  T :BuffergatorTabsClose
nnoremap <silent>  tc :BuffergatorTabsClose
nnoremap <silent>  to :BuffergatorTabsOpen
nnoremap <silent>  B :BuffergatorClose
nnoremap <silent>  b :call conque_gdb#toggle_breakpoint(expand("%:p"), line("."))
nmap <silent>  ba <Plug>BufKillAlt
nmap <silent>  bundo <Plug>BufKillUndo
nmap <silent>  !bw <Plug>BufKillBangBw
nmap <silent>  bw <Plug>BufKillBw
nmap <silent>  !bd <Plug>BufKillBangBd
nmap <silent>  bd <Plug>BufKillBd
nmap <silent>  !bun <Plug>BufKillBangBun
nmap <silent>  bun <Plug>BufKillBun
nmap <silent>  bf <Plug>BufKillForward
nmap <silent>  bb <Plug>BufKillBack
nmap  ca <Plug>NERDCommenterAltDelims
xmap  cu <Plug>NERDCommenterUncomment
nmap  cu <Plug>NERDCommenterUncomment
xmap  cb <Plug>NERDCommenterAlignBoth
nmap  cb <Plug>NERDCommenterAlignBoth
xmap  cl <Plug>NERDCommenterAlignLeft
nmap  cl <Plug>NERDCommenterAlignLeft
nmap  cA <Plug>NERDCommenterAppend
xmap  cy <Plug>NERDCommenterYank
nmap  cy <Plug>NERDCommenterYank
xmap  cs <Plug>NERDCommenterSexy
nmap  cs <Plug>NERDCommenterSexy
xmap  ci <Plug>NERDCommenterInvert
nmap  ci <Plug>NERDCommenterInvert
nmap  c$ <Plug>NERDCommenterToEOL
xmap  cn <Plug>NERDCommenterNested
nmap  cn <Plug>NERDCommenterNested
xmap  cm <Plug>NERDCommenterMinimal
nmap  cm <Plug>NERDCommenterMinimal
xmap  c  <Plug>NERDCommenterToggle
nmap  c  <Plug>NERDCommenterToggle
xmap  cc <Plug>NERDCommenterComment
nmap  cc <Plug>NERDCommenterComment
nnoremap <silent>  n :call conque_gdb#command("next")
nnoremap  cd :cd %:p:h:pwd
noremap  P "*p
noremap  Y "*y
vnoremap  p "+p
onoremap  p "+p
noremap  y "+y
nmap  d <Plug>(ale_fix)
nmap <silent>  j <Plug>(ale_next_wrap)
nmap <silent>  k <Plug>(ale_previous_wrap)
nnoremap  g :Ag 
vmap  d :YcmCompleter GoToDeclaration
omap  d :YcmCompleter GoToDeclaration
vmap  f :NERDTreeToggle
omap  f :NERDTreeToggle
map  e :e =escape(expand("%:p:h"),' ') . '/'
nnoremap <silent>  r :call conque_gdb#command("run")
vmap  s :w
omap  s :w
nnoremap <silent>  ] :exe "resize " . (winheight(0) * 2/3)
nnoremap <silent>  [ :exe "resize " . (winheight(0) * 3/2)
nnoremap  = =
nnoremap  . :vertical resize -5
nnoremap  , :vertical resize +5
nnoremap  	 p
nnoremap    
nnoremap <silent>  t :call conque_gdb#command("backtrace")
nmap  W :BD!
nmap  w :BD
nmap  h :bp
nmap  l :bn
nnoremap  Q :qa!
nnoremap  q :q
map # <Plug>ImprovedStar_#<Plug>SearchIndex
nnoremap <silent> '[ :call signature#mark#Goto("prev", "line", "alpha")
nnoremap <silent> '] :call signature#mark#Goto("next", "line", "alpha")
noremap * *
nmap - :m -2
xnoremap <silent> :<C-U>call multiple_cursors#select_all("v", 0)
xnoremap <silent> :call multiple_cursors#select_all("v", 0)
nnoremap <silent> :call multiple_cursors#select_all("n", 1)
nmap = :m +1
nnoremap H ^
noremap J :call smooth_scroll#down(3, 6, 1)
noremap K :call smooth_scroll#up(3, 6, 1)
nnoremap L $
nmap <silent> N N<Plug>SearchIndex
nnoremap P P=`]
nnoremap Q @q
xmap S <Plug>VSurround
map W q
nnoremap <silent> [= :call signature#marker#Goto("prev", "any",  v:count)
nnoremap <silent> [- :call signature#marker#Goto("prev", "same", v:count)
nnoremap <silent> [` :call signature#mark#Goto("prev", "spot", "pos")
nnoremap <silent> [' :call signature#mark#Goto("prev", "line", "pos")
nnoremap <silent> [b :bp
nnoremap <silent> ]= :call signature#marker#Goto("next", "any",  v:count)
nnoremap <silent> ]- :call signature#marker#Goto("next", "same", v:count)
nnoremap <silent> ]` :call signature#mark#Goto("next", "spot", "pos")
nnoremap <silent> ]' :call signature#mark#Goto("next", "line", "pos")
nnoremap <silent> ]b :bn
nnoremap <silent> `[ :call signature#mark#Goto("prev", "spot", "alpha")
nnoremap <silent> `] :call signature#mark#Goto("next", "spot", "alpha")
nmap cr <Plug>(abolish-coerce-word)
nmap cS <Plug>CSurround
nmap cs <Plug>Csurround
nnoremap <silent> dm :call signature#utils#Remove(v:count)
nmap ds <Plug>Dsurround
vmap gx <Plug>NetrwBrowseXVis
nmap gx <Plug>NetrwBrowseX
map g# <Plug>ImprovedStar_g#<Plug>SearchIndex
map g* <Plug>ImprovedStar_g*<Plug>SearchIndex
nmap g/ <Plug>SearchIndex
nnoremap <silent> gB :BuffergatorMruCycleNext
nnoremap <silent> gb :BuffergatorMruCyclePrev
xnoremap <silent> g<C-N> :call multiple_cursors#new("v", 0)
xnoremap <silent> g :call multiple_cursors#new("v", 0)
nnoremap <silent> g<C-N> :call multiple_cursors#new("n", 0)
nnoremap <silent> g :call multiple_cursors#new("n", 0)
xmap gr <Plug>ReplaceWithRegisterVisual
nmap grr <Plug>ReplaceWithRegisterLine
nmap gr <Plug>ReplaceWithRegisterOperator
nmap gcu <Plug>Commentary<Plug>Commentary
nmap gcc <Plug>CommentaryLine
omap gc <Plug>Commentary
nmap gc <Plug>Commentary
xmap gc <Plug>Commentary
xmap gS <Plug>VgSurround
nmap j gj
nmap k gk
nnoremap <silent> m? :call signature#marker#List(v:count, 0)
nnoremap <silent> m/ :call signature#mark#List(0, 0)
nnoremap <silent> m<BS> :call signature#marker#Purge()
nnoremap <silent> m  :call signature#mark#Purge("all")
nnoremap <silent> m- :call signature#mark#Purge("line")
nnoremap <silent> m. :call signature#mark#ToggleAtLine()
nnoremap <silent> m, :call signature#mark#Toggle("next")
nnoremap <silent> m :call signature#utils#Input()
nmap <silent> n n<Plug>SearchIndex
nnoremap p p=`]
map ss s
map vv v
nmap ySS <Plug>YSsurround
nmap ySs <Plug>YSsurround
nmap yss <Plug>Yssurround
nmap yS <Plug>YSurround
nmap ys <Plug>Ysurround
nmap zuz <Plug>(FastFoldUpdate)
nnoremap <Plug>(-fzf-:) :
nnoremap <Plug>(-fzf-/) /
nnoremap <Plug>(-fzf-vim-do) :execute g:__fzf_command
nnoremap <SNR>141_: :=v:count ? v:count : ''
vnoremap <silent> <Plug>NetrwBrowseXVis :call netrw#BrowseXVis()
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#BrowseX(expand((exists("g:netrw_gx")? g:netrw_gx : '<cfile>')),netrw#CheckIfRemote())
nnoremap <silent> <F11> :call conque_term#exec_file()
vnoremap <Plug>SearchIndex <Nop>
onoremap <Plug>SearchIndex <Nop>
nnoremap <silent> <M-S-B> :BuffergatorMruCycleNext
nnoremap <silent> <M-b> :BuffergatorMruCyclePrev
nnoremap <silent> <Plug>(FastFoldUpdate) :FastFoldUpdate!
nnoremap <silent> <Plug>(ale_rename) :ALERename
nnoremap <silent> <Plug>(ale_documentation) :ALEDocumentation
nnoremap <silent> <Plug>(ale_hover) :ALEHover
nnoremap <silent> <Plug>(ale_find_references) :ALEFindReferences
nnoremap <silent> <Plug>(ale_go_to_type_definition_in_vsplit) :ALEGoToTypeDefinitionInVSplit
nnoremap <silent> <Plug>(ale_go_to_type_definition_in_split) :ALEGoToTypeDefinitionInSplit
nnoremap <silent> <Plug>(ale_go_to_type_definition_in_tab) :ALEGoToTypeDefinitionInTab
nnoremap <silent> <Plug>(ale_go_to_type_definition) :ALEGoToTypeDefinition
nnoremap <silent> <Plug>(ale_go_to_definition_in_vsplit) :ALEGoToDefinitionInVSplit
nnoremap <silent> <Plug>(ale_go_to_definition_in_split) :ALEGoToDefinitionInSplit
nnoremap <silent> <Plug>(ale_go_to_definition_in_tab) :ALEGoToDefinitionInTab
nnoremap <silent> <Plug>(ale_go_to_definition) :ALEGoToDefinition
nnoremap <silent> <Plug>(ale_fix) :ALEFix
nnoremap <silent> <Plug>(ale_detail) :ALEDetail
nnoremap <silent> <Plug>(ale_lint) :ALELint
nnoremap <silent> <Plug>(ale_reset_buffer) :ALEResetBuffer
nnoremap <silent> <Plug>(ale_disable_buffer) :ALEDisableBuffer
nnoremap <silent> <Plug>(ale_enable_buffer) :ALEEnableBuffer
nnoremap <silent> <Plug>(ale_toggle_buffer) :ALEToggleBuffer
nnoremap <silent> <Plug>(ale_reset) :ALEReset
nnoremap <silent> <Plug>(ale_disable) :ALEDisable
nnoremap <silent> <Plug>(ale_enable) :ALEEnable
nnoremap <silent> <Plug>(ale_toggle) :ALEToggle
nnoremap <silent> <Plug>(ale_last) :ALELast
nnoremap <silent> <Plug>(ale_first) :ALEFirst
nnoremap <silent> <Plug>(ale_next_wrap_warning) :ALENext -wrap -warning
nnoremap <silent> <Plug>(ale_next_warning) :ALENext -warning
nnoremap <silent> <Plug>(ale_next_wrap_error) :ALENext -wrap -error
nnoremap <silent> <Plug>(ale_next_error) :ALENext -error
nnoremap <silent> <Plug>(ale_next_wrap) :ALENextWrap
nnoremap <silent> <Plug>(ale_next) :ALENext
nnoremap <silent> <Plug>(ale_previous_wrap_warning) :ALEPrevious -wrap -warning
nnoremap <silent> <Plug>(ale_previous_warning) :ALEPrevious -warning
nnoremap <silent> <Plug>(ale_previous_wrap_error) :ALEPrevious -wrap -error
nnoremap <silent> <Plug>(ale_previous_error) :ALEPrevious -error
nnoremap <silent> <Plug>(ale_previous_wrap) :ALEPreviousWrap
nnoremap <silent> <Plug>(ale_previous) :ALEPrevious
xnoremap <Plug>ColorFgBg :ColorSwapFgBg
nnoremap <Plug>ColorFgBg :ColorSwapFgBg
xnoremap <Plug>ColorContrast :ColorContrast
nnoremap <Plug>ColorContrast :ColorContrast
xnoremap <Plug>Colorizer :ColorHighlight
nnoremap <Plug>Colorizer :ColorToggle
nnoremap <silent> <Plug>GitGutterPreviewHunk :GitGutterPreviewHunk
nnoremap <silent> <Plug>GitGutterUndoHunk :GitGutterUndoHunk
nnoremap <silent> <Plug>GitGutterStageHunk :GitGutterStageHunk
nnoremap <silent> <expr> <Plug>GitGutterPrevHunk &diff ? '[c' : ":\execute v:count1 . 'GitGutterPrevHunk'\"
nnoremap <silent> <expr> <Plug>GitGutterNextHunk &diff ? ']c' : ":\execute v:count1 . 'GitGutterNextHunk'\"
xnoremap <silent> <Plug>GitGutterTextObjectOuterVisual :call gitgutter#hunk#text_object(0)
xnoremap <silent> <Plug>GitGutterTextObjectInnerVisual :call gitgutter#hunk#text_object(1)
onoremap <silent> <Plug>GitGutterTextObjectOuterPending :call gitgutter#hunk#text_object(0)
onoremap <silent> <Plug>GitGutterTextObjectInnerPending :call gitgutter#hunk#text_object(1)
snoremap <C-R> "_c
snoremap <silent> <C-H> c
snoremap <silent> <Del> c
snoremap <silent> <BS> c
snoremap <silent> <C-Tab> :call UltiSnips#ListSnippets()
xnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("x", "Uncomment")
nnoremap <silent> <Plug>NERDCommenterUncomment :call NERDComment("n", "Uncomment")
xnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("x", "AlignBoth")
nnoremap <silent> <Plug>NERDCommenterAlignBoth :call NERDComment("n", "AlignBoth")
xnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("x", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAlignLeft :call NERDComment("n", "AlignLeft")
nnoremap <silent> <Plug>NERDCommenterAppend :call NERDComment("n", "Append")
xnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("x", "Yank")
nnoremap <silent> <Plug>NERDCommenterYank :call NERDComment("n", "Yank")
xnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("x", "Sexy")
nnoremap <silent> <Plug>NERDCommenterSexy :call NERDComment("n", "Sexy")
xnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("x", "Invert")
nnoremap <silent> <Plug>NERDCommenterInvert :call NERDComment("n", "Invert")
nnoremap <silent> <Plug>NERDCommenterToEOL :call NERDComment("n", "ToEOL")
xnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("x", "Nested")
nnoremap <silent> <Plug>NERDCommenterNested :call NERDComment("n", "Nested")
xnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("x", "Minimal")
nnoremap <silent> <Plug>NERDCommenterMinimal :call NERDComment("n", "Minimal")
xnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("x", "Toggle")
nnoremap <silent> <Plug>NERDCommenterToggle :call NERDComment("n", "Toggle")
xnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("x", "Comment")
nnoremap <silent> <Plug>NERDCommenterComment :call NERDComment("n", "Comment")
xnoremap <silent> <C-N> :call multiple_cursors#new("v", 0)
nnoremap <silent> <C-N> :call multiple_cursors#new("n", 1)
nnoremap <silent> <Plug>ReplaceWithRegisterVisual :call setline('.', getline('.'))|execute 'silent! call repeat#setreg("\<Plug>ReplaceWithRegisterVisual", v:register)'|call ReplaceWithRegister#SetRegister()|if ReplaceWithRegister#IsExprReg()|    let g:ReplaceWithRegister_expr = getreg('=')|endif|execute 'normal!' ReplaceWithRegister#VisualMode()|call ReplaceWithRegister#Operator('visual', "\<Plug>ReplaceWithRegisterVisual")
vnoremap <silent> <Plug>ReplaceWithRegisterVisual :call setline('.', getline('.'))|execute 'silent! call repeat#setreg("\<Plug>ReplaceWithRegisterVisual", v:register)'|call ReplaceWithRegister#SetRegister()|if ReplaceWithRegister#IsExprReg()|    let g:ReplaceWithRegister_expr = getreg('=')|endif|call ReplaceWithRegister#Operator('visual', "\<Plug>ReplaceWithRegisterVisual")
nnoremap <silent> <Plug>ReplaceWithRegisterLine :call setline('.', getline('.'))|execute 'silent! call repeat#setreg("\<Plug>ReplaceWithRegisterLine", v:register)'|call ReplaceWithRegister#SetRegister()|if ReplaceWithRegister#IsExprReg()|    let g:ReplaceWithRegister_expr = getreg('=')|endif|execute 'normal! V' . v:count1 . "_\<Esc>"|call ReplaceWithRegister#Operator('visual', "\<Plug>ReplaceWithRegisterLine")
nnoremap <silent> <Plug>ReplaceWithRegisterExpressionSpecial :let g:ReplaceWithRegister_expr = getreg('=')|execute 'normal!' v:count1 . '.'
nnoremap <expr> <Plug>ReplaceWithRegisterOperator ReplaceWithRegister#OperatorExpression()
nmap <silent> <Plug>CommentaryUndo :echoerr "Change your <Plug>CommentaryUndo map to <Plug>Commentary<Plug>Commentary"
nnoremap <silent> <Plug>SurroundRepeat .
onoremap <silent> <Plug>(fzf-maps-o) :call fzf#vim#maps('o', 0)
xnoremap <silent> <Plug>(fzf-maps-x) :call fzf#vim#maps('x', 0)
nnoremap <silent> <Plug>(fzf-maps-n) :call fzf#vim#maps('n', 0)
nnoremap <Right> :vertical resize -2
nnoremap <Left> :vertical resize +2
nnoremap <Down> :resize -2
nnoremap <Up> :resize +2
nnoremap <C-G>d :Gdiff
nnoremap <C-G>s :Gstatus
nnoremap <C-G>? :GFiles?
nnoremap <C-G>p :GFiles
nnoremap <C-G>b :Gblame
nnoremap <C-G>c :BCommits
nnoremap <C-G>l :BLines
nnoremap <C-G>g :Ag
nnoremap <C-G>t :Buffers
nnoremap <C-P> :Files
imap S <Plug>ISurround
imap s <Plug>Isurround
inoremap <silent> 	 =UltiSnips#ExpandSnippet()
cmap <expr>  "\" . (getcmdtype() =~ '[/?]' ? "<Plug>SearchIndex" : "")
imap  <Plug>DiscretionaryEnd
inoremap <expr>  pumvisible() ? "\" : "\"
inoremap <expr>  pumvisible() ? "\" : "\"
imap  <Plug>Isurround
nnoremap <silent> Â :BuffergatorMruCycleNext
nnoremap <silent> â :BuffergatorMruCyclePrev
cnoremap jk 
inoremap jk 
let &cpo=s:cpo_save
unlet s:cpo_save
set autoindent
set autoread
set background=dark
set backspace=indent,eol,start
set clipboard=unnamed
set completeopt=preview,menuone
set cpoptions=aAceFsB
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set fillchars=vert:\ ,stl:\ ,stlnc:\\
set foldlevelstart=1
set guicursor=a:blinkon0
set guifont=Ubuntu\ Mono\ derivative\ Powerline:h16
set guioptions=aegimtT
set helplang=en
set hidden
set history=200
set hlsearch
set ignorecase
set incsearch
set laststatus=2
set linespace=2
set listchars=tab:\ \ ,trail:·
set mouse=a
set pyxversion=2
set regexpengine=1
set ruler
set runtimepath=~/.vim,~/.vim/pack/coq/start/coq.vim,~/.vim/pack/coq/start/coq-au-vim,~/.vim/bundle/nerdtree,~/.vim/bundle/fzf,~/.vim/bundle/fzf.vim,~/.vim/bundle/vim-eunuch,~/.vim/bundle/vim-indent-object,~/.vim/bundle/vim-surround,~/.vim/bundle/vim-commentary,~/.vim/bundle/ReplaceWithRegister,~/.vim/bundle/vim-repeat,~/.vim/bundle/auto-pairs,~/.vim/bundle/vim-multiple-cursors,~/.vim/bundle/nerdcommenter,~/.vim/bundle/vim-autoread,~/.vim/bundle/rainbow,~/.vim/bundle/ultisnips,~/.vim/bundle/vim-snippets,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/vim-airline,~/.vim/bundle/vim-airline-themes,~/.vim/bundle/vim-fugitive,~/.vim/bundle/vim-gitgutter,~/.vim/bundle/vim-bufkill,~/.vim/bundle/vim-slim,~/.vim/bundle/Colorizer,~/.vim/bundle/vim-javascript,~/.vim/bundle/vim-jsx,~/.vim/bundle/javascript-libraries-syntax.vim,~/.vim/bundle/vim-javascript-syntax,~/.vim/bundle/tern_for_vim,~/.vim/bundle/ale,~/.vim/bundle/vim-endwise,~/.vim/bundle/vim-smooth-scroll,~/.vim/bundle/fastfold,~/.vim/bundle/vim-buffergator,~/.vim/bundle/vim-diff-enhanced,~/.vim/bundle/vim-numbertoggle,~/.vim/bundle/vim-searchindex,~/.vim/bundle/vim-abolish,~/.vim/bundle/vim-stay,~/.vim/bundle/vim-signature,~/.vim/bundle/onedark.vim,~/.vim/bundle/vim-misc,~/.vim/bundle/vim-notes,~/.vim/bundle/Conque-GDB,/usr/share/vim/vimfiles,/usr/share/vim/vim81,/usr/share/vim/vim81/pack/dist/opt/termdebug,/usr/share/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.vim/bundle/nerdtree/after,~/.vim/bundle/fzf/after,~/.vim/bundle/fzf.vim/after,~/.vim/bundle/vim-eunuch/after,~/.vim/bundle/vim-indent-object/after,~/.vim/bundle/vim-surround/after,~/.vim/bundle/vim-commentary/after,~/.vim/bundle/ReplaceWithRegister/after,~/.vim/bundle/vim-repeat/after,~/.vim/bundle/auto-pairs/after,~/.vim/bundle/vim-multiple-cursors/after,~/.vim/bundle/nerdcommenter/after,~/.vim/bundle/vim-autoread/after,~/.vim/bundle/rainbow/after,~/.vim/bundle/ultisnips/after,~/.vim/bundle/vim-snippets/after,~/.vim/bundle/YouCompleteMe/after,~/.vim/bundle/vim-airline/after,~/.vim/bundle/vim-airline-themes/after,~/.vim/bundle/vim-fugitive/after,~/.vim/bundle/vim-gitgutter/after,~/.vim/bundle/vim-bufkill/after,~/.vim/bundle/vim-slim/after,~/.vim/bundle/Colorizer/after,~/.vim/bundle/vim-javascript/after,~/.vim/bundle/vim-jsx/after,~/.vim/bundle/javascript-libraries-syntax.vim/after,~/.vim/bundle/vim-javascript-syntax/after,~/.vim/bundle/tern_for_vim/after,~/.vim/bundle/ale/after,~/.vim/bundle/vim-endwise/after,~/.vim/bundle/vim-smooth-scroll/after,~/.vim/bundle/fastfold/after,~/.vim/bundle/vim-buffergator/after,~/.vim/bundle/vim-diff-enhanced/after,~/.vim/bundle/vim-numbertoggle/after,~/.vim/bundle/vim-searchindex/after,~/.vim/bundle/vim-abolish/after,~/.vim/bundle/vim-stay/after,~/.vim/bundle/vim-signature/after,~/.vim/bundle/onedark.vim/after,~/.vim/bundle/vim-misc/after,~/.vim/bundle/vim-notes/after,~/.vim/bundle/Conque-GDB/after
set scrolloff=8
set shiftwidth=4
set shortmess=filnxtToOSsc
set showcmd
set noshowmode
set showtabline=2
set sidescroll=1
set sidescrolloff=15
set smartcase
set smartindent
set smarttab
set softtabstop=4
set splitbelow
set splitright
set statusline=%=&P\ %f\ %m
set suffixes=.bak,~,.swp,.o,.info,.aux,.log,.dvi,.bbl,.blg,.brf,.cb,.ind,.idx,.ilg,.inx,.out,.toc,.png,.jpg
set noswapfile
set tabline=%!airline#extensions#tabline#get()
set tabstop=4
set termguicolors
set ttimeoutlen=10
set updatetime=100
set viewoptions=cursor,folds,slash,unix
set viminfo='100,<50,s10,h,n~/.vim/viminfo
set visualbell
set nowritebackup
let s:so_save = &so | let s:siso_save = &siso | set so=0 siso=0
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/Programmation/homenetctl
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
set shortmess=aoO
argglobal
%argdel
set splitbelow splitright
wincmd t
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
argglobal
enew
let s:cpo_save=&cpo
set cpo&vim
inoremap <buffer> <silent> <C-S> :call AutoPairsJump()a
inoremap <buffer> <silent> <expr> <M-p> AutoPairsToggle()
inoremap <buffer> <silent> <M-b> =AutoPairsBackInsert()
inoremap <buffer> <silent> <M-e> =AutoPairsFastWrap()
inoremap <buffer> <silent> <BS> =AutoPairsDelete()
inoremap <buffer> <silent> <M-'> =AutoPairsMoveCharacter('''')
inoremap <buffer> <silent> <M-"> =AutoPairsMoveCharacter('"')
inoremap <buffer> <silent> <M-}> =AutoPairsMoveCharacter('}')
inoremap <buffer> <silent> <M-{> =AutoPairsMoveCharacter('{')
inoremap <buffer> <silent> <M-]> =AutoPairsMoveCharacter(']')
inoremap <buffer> <silent> <M-[> =AutoPairsMoveCharacter('[')
inoremap <buffer> <silent> <M-)> =AutoPairsMoveCharacter(')')
inoremap <buffer> <silent> <M-(> =AutoPairsMoveCharacter('(')
noremap <buffer> <silent>  :call AutoPairsJump()
nnoremap <buffer> <silent> ( :call CoqPreviousSentence(v:count)
nnoremap <buffer> <silent> ) :call CoqNextSentence(v:count)
inoremap <buffer> <silent> § =AutoPairsMoveCharacter('''')
inoremap <buffer> <silent> ¢ =AutoPairsMoveCharacter('"')
inoremap <buffer> <silent> © =AutoPairsMoveCharacter(')')
inoremap <buffer> <silent> ¨ =AutoPairsMoveCharacter('(')
inoremap <buffer> <silent> <expr> ð AutoPairsToggle()
inoremap <buffer> <silent> â =AutoPairsBackInsert()
inoremap <buffer> <silent> å =AutoPairsFastWrap()
inoremap <buffer> <silent> ý =AutoPairsMoveCharacter('}')
inoremap <buffer> <silent> û =AutoPairsMoveCharacter('{')
inoremap <buffer> <silent> Ý =AutoPairsMoveCharacter(']')
inoremap <buffer> <silent> Û =AutoPairsMoveCharacter('[')
vnoremap <buffer> <silent> as :call CoqVisualSentence(v:false)
vnoremap <buffer> <silent> is :call CoqVisualSentence(v:true)
noremap <buffer> <silent> <C-S> :call AutoPairsJump()
noremap <buffer> <silent> <M-p> :call AutoPairsToggle()
inoremap <buffer> <silent>  :call AutoPairsJump()a
inoremap <buffer> <silent>   =AutoPairsSpace()
inoremap <buffer> <silent> " =AutoPairsInsert('"')
inoremap <buffer> <silent> ' =AutoPairsInsert('''')
inoremap <buffer> <silent> ( =AutoPairsInsert('(')
inoremap <buffer> <silent> ) =AutoPairsInsert(')')
noremap <buffer> <silent> ð :call AutoPairsToggle()
inoremap <buffer> <silent> [ =AutoPairsInsert('[')
inoremap <buffer> <silent> ] =AutoPairsInsert(']')
inoremap <buffer> <silent> ` =AutoPairsInsert('`')
inoremap <buffer> <silent> { =AutoPairsInsert('{')
inoremap <buffer> <silent> } =AutoPairsInsert('}')
let &cpo=s:cpo_save
unlet s:cpo_save
setlocal keymap=
setlocal noarabic
setlocal autoindent
setlocal backupcopy=
setlocal balloonexpr=
setlocal nobinary
setlocal nobreakindent
setlocal breakindentopt=
setlocal bufhidden=
setlocal buflisted
setlocal buftype=
setlocal nocindent
setlocal cinkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal cinoptions=
setlocal cinwords=if,else,while,do,for,switch
set colorcolumn=80
setlocal colorcolumn=80
setlocal comments=s1:/*,mb:*,ex:*/,://,b:#,:%,:XCOMM,n:>,fb:-
setlocal commentstring=/*%s*/
setlocal complete=.,w,b,u,t,i
setlocal concealcursor=
setlocal conceallevel=0
setlocal completefunc=
setlocal nocopyindent
setlocal cryptmethod=
setlocal nocursorbind
setlocal nocursorcolumn
set cursorline
setlocal cursorline
setlocal cursorlineopt=both
setlocal define=
setlocal dictionary=
setlocal nodiff
setlocal equalprg=
setlocal errorformat=
setlocal expandtab
if &filetype != ''
setlocal filetype=
endif
setlocal fixendofline
setlocal foldcolumn=0
setlocal foldenable
setlocal foldexpr=CoqFoldLevel(v:lnum)
setlocal foldignore=#
setlocal foldlevel=1
setlocal foldmarker={{{,}}}
set foldmethod=syntax
setlocal foldmethod=syntax
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldtext=CoqFoldText()
setlocal formatexpr=
setlocal formatoptions=tcq
setlocal formatlistpat=^\\s*\\d\\+[\\]:.)}\\t\ ]\\s*
setlocal formatprg=
setlocal grepprg=
setlocal iminsert=0
setlocal imsearch=-1
setlocal include=
setlocal includeexpr=
setlocal indentexpr=
setlocal indentkeys=0{,0},0),0],:,0#,!^F,o,O,e
setlocal noinfercase
setlocal iskeyword=@,48-57,_,192-255
setlocal keywordprg=
set linebreak
setlocal linebreak
setlocal nolisp
setlocal lispwords=
set list
setlocal list
setlocal makeencoding=
setlocal makeprg=
setlocal matchpairs=(:),{:},[:]
setlocal modeline
setlocal modifiable
setlocal nrformats=bin,octal,hex
set number
setlocal number
setlocal numberwidth=4
setlocal omnifunc=
setlocal path=
setlocal nopreserveindent
setlocal nopreviewwindow
setlocal quoteescape=\\
setlocal noreadonly
set relativenumber
setlocal relativenumber
setlocal norightleft
setlocal rightleftcmd=search
setlocal noscrollbind
setlocal scrolloff=-1
setlocal shiftwidth=2
setlocal noshortname
setlocal sidescrolloff=-1
setlocal signcolumn=auto
setlocal smartindent
setlocal softtabstop=4
setlocal nospell
setlocal spellcapcheck=[.?!]\\_[\\])'\"\	\ ]\\+
setlocal spellfile=
setlocal spelllang=en
setlocal statusline=%!airline#statusline(1)
setlocal suffixesadd=
setlocal noswapfile
setlocal synmaxcol=3000
if &syntax != ''
setlocal syntax=
endif
setlocal tabstop=2
setlocal tagcase=
setlocal tagfunc=
setlocal tags=
setlocal termwinkey=
setlocal termwinscroll=10000
setlocal termwinsize=
setlocal textwidth=0
setlocal thesaurus=
setlocal noundofile
setlocal undolevels=-123456
setlocal varsofttabstop=
setlocal vartabstop=
setlocal wincolor=
setlocal nowinfixheight
setlocal nowinfixwidth
setlocal wrap
setlocal wrapmargin=0
tabnext 1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20 shortmess=filnxtToOSsc
set winminheight=1 winminwidth=1
let s:sx = expand("<sfile>:p:r")."x.vim"
if file_readable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &so = s:so_save | let &siso = s:siso_save
nohlsearch
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
