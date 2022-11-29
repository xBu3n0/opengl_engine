type Re = Double
type Im = Double
type Complex = (Re, Im)
type Pixel = Complex

xCoord :: [Re]
xCoord =  [-2, -1.998 .. 2]
yCoord :: [Im]
yCoord =  [-2, -1.998 .. 2]
maxIterration :: Int
maxIterration = 1000

mag :: Complex -> Double
mag (x, y) = x^2 + y^2
add :: Complex -> Complex -> Complex
add (x0, y0) (x1, y1) = (x0+x1, y0+y1)
square :: Complex -> Complex
square (x, y) = (x*x-y*y, 2*x*y)

pixels :: [Pixel]
pixels = [(x, y) | y <- yCoord, x <- xCoord]

solve :: [Pixel] -> (Complex -> Complex -> Int -> String) -> String
solve [] _ = ""
solve [z] f = f z z 0
solve (z:zs)  f = f z z 0 ++ solve zs f


mandelbrot :: Complex -> Complex -> Int -> String
mandelbrot z_it z_0 it
   | mag next > 4 =
    show rValue ++ " " ++ show gValue ++ " " ++ show bValue ++ " "
   | it > maxIterration =
    "0 0 0 "
   | otherwise =
    mandelbrot next z_0 (it+1)
   where
       next   = add (square z_it) z_0
       rValue = mod (truncate (300.0 * sin (fromIntegral it :: Double))) 256
       gValue = mod (truncate (130.0 * cos (fromIntegral it :: Double))) 256
       bValue = mod (  truncate (217.0 * fromIntegral it :: Double)    ) 256


main :: IO ()
main =
    writeFile "mandelbrot.ppm" $ "P3 " ++ xPixel ++ " " ++ yPixel ++ color ++ solve pixels mandelbrot
    where
        xPixel = show (length xCoord)
        yPixel = show (length yCoord)
        color = " 255\n"
