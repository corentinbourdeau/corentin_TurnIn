import System.Exit

addIntegers :: Int -> Int -> Int
addIntegers x y = x + y

main :: IO ()
main = do
    let x = 1
    let y = 3
    putStr "Sum of "
    putStr $ show x
    putStr " + "
    putStr $ show y
    putStr " = "
    print(addIntegers x y)
    exitWith ExitSuccess 
