
library(igraph)

file_path <- "numsOfTriangle\\7truss_out1.txt"

edge_list <- read.table(file_path, header = FALSE)
graph <- graph_from_data_frame(edge_list, directed = FALSE)
graph <- simplify(graph)
l <- layout_with_fr(graph)


plot(graph, 
    layout = l,
    vertex.size= 1, #0.02
    edge.arrow.size=1, #0.001
    vertex.label.cex = 0.75,
    vertex.label.color = "black",
    vertex.frame.color = adjustcolor("white", alpha.f = 0),
    vertex.color = adjustcolor("black", alpha.f = 0),
    edge.color=adjustcolor("blue", alpha.f = 0.15),
    display.isolates=FALSE,vertex.label=ifelse(page_rank(graph)$vector > 0.1 ,
     "important nodes",NA),
     main = "Visualize")