#pragma once

// compute log (1+x) using its Maclaurin series, up to the first 'nelem'
// elements in the series (with default number set to 10):
double log_one_plus_x (const double x, const int nelem = 10);

