set tabstop=4
set softtabstop=4
set shiftwidth=4
set noexpandtab
set colorcolumn=110
highlight ColorColumn ctermbg=darkgray
set makeprg=make\ -j8
nnoremap <F4> :make!<cr>
nnoremap <F5> :!./countingCars<cr>
nnoremap <F6> :make! clean<cr>
nnoremap <F7> :make!<cr>:!./countingCars<cr>
