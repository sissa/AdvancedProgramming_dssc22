set terminal gif animate delay 5
set output 'jacobi.gif'


set size square
unset colorbox
set palette rgb 33,13,10
set yr [] reverse #otherwise it flips the image due to default axis orientation

mod = 10

do for [i=0:(system("ls gif_dir/ | wc -l")-1)/mod] {
   num=mod*i
   plot './gif_dir/'.num.'.dat' matrix with image title "Frame".i."/".(system("ls gif_dir/ | wc -l")/mod)
} 


reset 
set output
set terminal qt #just to return back to normal output terminal; MIGHT NOT BE QT ON YOUR SYSTEM 
 
 
