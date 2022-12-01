#run this file with `python anim.py` from command line
#open the .gif in whatever you usually open them with to check that it worked
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
fig=plt.figure()
#you can put something depending on i here
def animate(i): 
    plt.imshow(np.random.random((50,50)))
 
anim = animation.FuncAnimation(fig,animate,frames=10, interval=10)

# save the animation as an gif
anim.save("animation_example.gif") 
