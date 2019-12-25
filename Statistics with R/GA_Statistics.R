statistics=function(x){
  oneLine <- readLines(x, n = 1, warn = FALSE)
  while (TRUE) {
    if(isTRUE(strcmp(oneLine[1],"ga"))){
      cat("\nResults for Genetic Algorithm:\n\n")
      weight = vector()
      time = vector()
      oneLine <- readLines(x, n = 1, warn = FALSE)
      while ((length(oneLine) > 0) && isFALSE(strcmp(oneLine[1],"sa")) && isFALSE(strcmp(oneLine[1],"ga"))) {
        var = unlist(strsplit(oneLine, ";"))
        weight = c(weight, as.double(var[1]))
        time = c(time, as.double(var[2]))
        oneLine <- readLines(x, n = 1, warn = FALSE)
      }
      a=min(weight)
      b=max(weight)
      c=mean(weight)
      d=sd(weight)
      e=mean(time)
      print(list(a,b,c,d,e))
      if(length(oneLine) == 0)
        break
    }
    else{
      cat("\nResults for Simulated Annealing:\n\n")
      weight = vector()
      time = vector()
      oneLine <- readLines(x, n = 1, warn = FALSE)
      while ((length(oneLine) > 0) && isFALSE(strcmp(oneLine[1],"ga")) && isFALSE(strcmp(oneLine[1],"sa"))) {
        var = unlist(strsplit(oneLine, ";"))
        weight = c(weight, as.double(var[1]))
        time = c(time, as.double(var[2]))
        oneLine <- readLines(x, n = 1, warn = FALSE)
      }
      a=min(weight)
      b=max(weight)
      c=mean(weight)
      d=sd(weight)
      e=mean(time)
      print(list(a,b,c,d,e))
      if(length(oneLine) == 0)
        break
    }
  }
  
}
library(pracma)
file.list <- list.files(path = "C:/Users/Ciprian/Desktop/Materiale/Facultate/Anul 2/Semestrul 1/Algoritmi genetici (AG)/T3/Genetic-Algorithm-TSP/Genetic-Algorithm-TSP/results/", pattern="*.txt", full.names=TRUE)
print("-----------------------------------------------------", quote = FALSE)
for (item in 1:length(file.list)) {
  cat("Results for data from file ")
  cat(basename(file.list[item]))
  cat("\n")
  df = file(file.list[item], open = "r")
  statistics(df)
  print("-----------------------------------------------------", quote = FALSE)
  close(df)
}