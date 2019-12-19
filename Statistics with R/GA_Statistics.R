statistics=function(x){
  values = vector()
  weight = vector()
  time = vector()
  while (length(oneLine <- readLines(x, n = 1, warn = FALSE)) > 0) {
    var = unlist(strsplit(oneLine, ";"))
    values = c(values, as.double(unlist(strsplit(var[1], " "))))
    weight = c(weight, as.double(var[2]))
    time = c(time, as.double(var[3]))
  }
  a=min(weight)
  b=max(weight)
  c=mean(weight)
  d=sd(weight)
  e=mean(time)
  print(list(a,b,c,d,e))
}
file.list <- list.files(path = "C:/Users/Ciprian/Desktop/Materiale/Facultate/Anul 2/Semestrul 1/Algoritmi genetici (AG)/T3/Genetic-Algorithm-TSP/Genetic-Algorithm-TSP/results/", pattern="*.txt", full.names=TRUE)
print("-----------------------------------------------------", quote = FALSE)
for (item in 1:length(file.list)) {
  df = file(file.list[item], open = "r")
  statistics(df)
  print("-----------------------------------------------------", quote = FALSE)
  close(df)
}
