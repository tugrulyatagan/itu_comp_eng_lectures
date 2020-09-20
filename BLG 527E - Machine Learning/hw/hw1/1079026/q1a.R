# BLG 527E Machine Learning HW1 Q1a
# Author: Tugrul Yatagan 504161551

i <- 500
N <- 10
x <- replicate(i, mean(runif(N)))

hist(x,
     breaks=c(seq(0, 1, 0.025)),
     xlim=c(0, 1),
     axes = F,
     xlab = sprintf("mean of %d random samples", N),
     main = sprintf("Q1a: N=%d", N))

axis(1, at=seq(0, 1, 0.025))
axis(2)
