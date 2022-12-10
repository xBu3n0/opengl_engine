data Expr =
      Val           Rational
    | Add           Expr Expr
    | Neg           Expr
    | Div           Expr Expr
    | Mult          Expr Expr
    deriving (Show)

solve:: Expr -> Rational
solve (Val x)   = x
solve (Add x y) = solve x + solve y
solve (Neg x)   = -solve x
solve (Div x y) = solve x / solve y
solve (Mult x y) = solve x * solve y


main :: IO ()
main =
    print $ solve x
    where
        x = Div (Add (Val 7) (Div (Val 8) (Val 2))) (Val 11)