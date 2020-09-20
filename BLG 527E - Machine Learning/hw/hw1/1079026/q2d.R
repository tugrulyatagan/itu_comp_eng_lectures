# BLG 527E Machine Learning HW1 Q2d
# Author: Tugrul Yatagan 504161551

range <- 10

g1_x_func <- function(x) {
  log(1/(sqrt(2*pi))) - (x^2)/2 + log(0.2)
}

g2_x_func <- function(x) {
  log(1/(2*sqrt(2*pi))) - ((x-1)^2)/8 + log(0.8)
}

plot(g1_x_func, -range, range, col='blue', main = "Q2d: g1(x)[Blue] and g2(x)[Red]", ylab = "gi(x)")
plot(g2_x_func, -range, range, col='red', add = T)
