# BLG 527E Machine Learning HW1 Q2b2
# Author: Tugrul Yatagan 504161551

sample_num <- 10000
range <- 6


p_c1_x_func <- function(x) {
  exp((-x^2)/2) / ( exp((-x^2)/2) + 0.5 * exp(-((x-1)^2)/8) )
}

p_c2_x_func <- function(x) {
  0.5 * exp(-((x-1)^2)/8) / ( exp((-x^2)/2) + 0.5 * exp(-((x-1)^2)/8) )
}

plot(p_c1_x_func, -range, range, col='blue', main = "Q2b2: P(C1|x)[Blue] and P(C2|x)[Red]", ylab = "P(Ci|x)", ylim=c(0, 1))
plot(p_c2_x_func, -range, range, col='red', add = T)

rt1 <- uniroot(function(x)  p_c1_x_func(x) - p_c2_x_func(x)  , c(0,range), tol=1e-8)     
rt2 <- uniroot(function(x)  p_c1_x_func(x) - p_c2_x_func(x)  , c(-range,0), tol=1e-8)     

rt1$root
rt2$root

abline(v=rt1$root, col="green")
abline(v=rt2$root, col="green")