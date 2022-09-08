# connect4
A simple console-based connect4 game

Note: the console display utilitzes linux-based color codes.

      If the machine you are running on does not support, a simple fix is replacing:
      
        line 46's color string with "X"
        line 49's color string with "O"
          based on preference, either "X" and "O" may be swapped
          
        line 52 with " "
           Note: "O" was used a placeholder to mark an empty slot and worked 
                 best visually with colors, however a simple blank will perform better
                 to distinguish an "O" token with a blank
                 
        line 171's color strings with "[" and "]" respectivley
