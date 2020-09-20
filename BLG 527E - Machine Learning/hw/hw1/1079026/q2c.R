# BLG 527E Machine Learning HW1 Q2c
# Author: Tugrul Yatagan 504161551

range <- 5

g1_x_func <- function(x) {
  log(1/(2*sqrt(2*pi))) - (x^2)/2
}

g2_x_func <- function(x) {
  log(1/(4*sqrt(2*pi))) - ((x-1)^2)/8
}

plot(g1_x_func, -range, range, col='blue', main = "Q2c: g1(x)[Blue] and g2(x)[Red]", ylab = "gi(x)")
plot(g2_x_func, -range, range, col='red', add = T)

rt1 <- uniroot(function(x)  g1_x_func(x) - g2_x_func(x)  , c(0,range), tol=1e-8)     
rt2 <- uniroot(function(x)  g1_x_func(x) - g2_x_func(x)  , c(-range,0), tol=1e-8)     

rt1$root
rt2$root

abline(v=rt1$root, col="green")
abline(v=rt2$root, col="green")
