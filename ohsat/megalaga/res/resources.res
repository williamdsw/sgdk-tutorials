# IMAGE objName "path" BEST ALL
IMAGE background "images/tilesets/space.bmp" FAST ALL

# SPRITE objName "path" tile_width tile_height FAST animation_framerate
SPRITE ship "images/spritesheets/ship.bmp" 2 2 FAST 6
SPRITE bullet "images/sprites/bullet.bmp" 1 1 FAST 0
SPRITE powerUpSprite "images/sprites/powerup.bmp" 1 1 FAST 0

# WAV objName "path" sound_engine (XGM)
WAV laserSFX "audios/sfx/laser.wav" 5 
WAV explosionSFX "audios/sfx/explosion.wav" 5