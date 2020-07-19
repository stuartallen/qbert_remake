# Run this to create a statically-linked version of the code.
# got this from https://blog.wasin.io/2018/10/18/statically-build-sdl2-application.html
# worked around missing ModPlug & Ogg symbols by ignoring since we don't use those
# functions.
clang++ -std=c++11 \
  -I/usr/local/opt/sdl2/include/SDL2 \
  -I/usr/local/opt/sdl2_gfx/include/SDL2 \
  -I/usr/local/opt/sdl2_mixer/include/SDL2 \
  *.cpp -o qbert \
  /usr/local/opt/sdl2/lib/libSDL2.a \
  /usr/local/opt/sdl2_gfx/lib/libSDL2_gfx.a \
  /usr/local/opt/sdl2_mixer/lib/libSDL2_mixer.a \
  -lm -liconv \
  -Wl,-U,_ModPlug_GetSettings \
  -Wl,-U,_ModPlug_Load \
  -Wl,-U,_ModPlug_Read \
  -Wl,-U,_ModPlug_Seek \
  -Wl,-U,_ModPlug_SetMasterVolume \
  -Wl,-U,_ModPlug_SetSettings \
  -Wl,-U,_ModPlug_Unload \
  -Wl,-U,_ov_clear \
  -Wl,-U,_ov_comment \
  -Wl,-U,_ov_info \
  -Wl,-U,_ov_open_callbacks \
  -Wl,-U,_ov_pcm_seek \
  -Wl,-U,_ov_pcm_tell \
  -Wl,-U,_ov_pcm_total \
  -Wl,-U,_ov_read \
  -Wl,-U,_ov_time_seek \
  -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,CoreVideo -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-weak_framework,QuartzCore -Wl,-weak_framework,Metal 
