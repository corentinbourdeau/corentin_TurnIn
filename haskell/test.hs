import System.Exit

addIntegers :: Int -> Int -> Int
addIntegers x y = x + y

charType :: Char -> Char
charType c = 'K'

data Area = Circle Float Float Float

surfaces :: Area -> Float
surfaces (Circle _ _ r) = pi * r ^ 2

main :: IO ()
main = do
-- This variables can be changed
    let x = 1
    let y = 3
    putStr "Sum of "
    putStr $ show x
    putStr " + "
    putStr $ show y
    putStr " = "
    print(addIntegers x y)

-- This variable can be changed
    let var = 21
    if var == 0
        then putStrLn "Number is zero"
    else if var `rem` 2 == 0
        then putStrLn "Number is even"
    else putStrLn "Number is odd"

-- This variable can be changed
    let a = 'a'
    let b = 'b'
    print (charType a)

-- This variable can be changed
    print (show [-5..10])

    print(surfaces $ Circle 1.7 2.3 10.1)


    exitWith ExitSuccess 
