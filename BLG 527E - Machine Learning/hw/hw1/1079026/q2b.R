# BLG 527E Machine Learning HW1 Q2b
# Author: Tugrul Yatagan 504161551

# Uncomment following lines to install ggplot2 library
#install.packages("ggplot2")
#install.packages("Rcpp")
#install.packages("colorspace")

library(ggplot2)

sample_num <- 10000
range <- 6

hist(rnorm(sample_num, 0, 1), border = F, col = 'blue', freq = F, xlim=c(-range, range), main = "Q2b: N(0,1)[Blue] and N(1,0)[Red]", xlab = "Values")
hist(rnorm(sample_num, 1, 2), border = F, col = scales::alpha('red', 0.5), freq = F, add = T, xlim=c(-range, range))

lines(seq(-range, range, 0.1), dnorm(seq(-range, range, 0.1), 0, 1), col='blue')
lines(seq(-range, range, 0.1), dnorm(seq(-range, range, 0.1), 1, 2), col='red')