@echo off
python "%~dp0playgame.py" --engine_seed 42 --player_seed 42 --end_wait=0.25 --verbose --log_dir game_logs --turns 100 --map_file "%~dp0maps\cell_maze\cell_maze_p06_03.map" %* "python ""%~dp0sample_bots\python\GreedyBot.py""" "python ""%~dp0sample_bots\python\LeftyBot.py""" "python ""%~dp0sample_bots\python\HunterBot.py""" "python ""%~dp0sample_bots\python\RandomBot.py""" "./bots/AntBot.exe" "./bots/AntBot.exe"

