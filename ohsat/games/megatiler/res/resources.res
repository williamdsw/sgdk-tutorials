# IMAGE objName "path" BEST ALL
IMAGE imgFloorTiles "images/tilesheets/tilesheet.png" 0

# SPRITE objName "path" tile_width tile_height FAST animation_speed
# 1 tile = 8 pixels
SPRITE sprPlayer "images/spritesheets/player.png" 1 1 NONE 20
SPRITE sprCoin "images/spritesheets/coin.png" 1 1 NONE 20

# WAV objName "path" audio_driver
WAV sfxCoin "audio/sfx/coin.wav" 0
WAV sfxUnlock "audio/sfx/unlock.wav" 0