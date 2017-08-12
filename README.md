# Hits and Google PageRank

Description:<br/>
->Calculates Hubs and Authority values and PageRank values based on the input graph, iteration and initial value.<br/>
->Iteration value -1 to -6 define the error rate as 10^-1 to 10^-6 respectively which means that the calculations stop<br/>
&nbsp;&nbsp;&nbsp;&nbsp;after the error rate reaches upto the precision specified.<br/>
->Iteration value greater than 0 define the number of iteration.<br/>
->Initial value of -1 and -2 initializes the starting values as 1/N and 1/sqrt(N) respectively where N is the number of webpages<br/>
->Initial value of 0 or 1 initializes the starting values as 0 or 1.<br/>
->The code is documented for reference.
