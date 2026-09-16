# Phase 2 — Object System

Type Player

    Detail Name
    Detail Money
    Detail Level

    Start Name
        Set This.Name = Name
        Set This.Money = 0
        Set This.Level = 1
    End

    Function GiveMoney Amount
        Change This.Money by Amount
        Give Back This.Money
    End

End

Create Player Adan

Call Adan.GiveMoney 100
