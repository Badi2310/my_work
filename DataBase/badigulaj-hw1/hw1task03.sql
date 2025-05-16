select count(703 * 1.0001092375 * weight / power(height, 2)) underweight_count
from hw
where 703 * 1.0001092375 * weight / power(height, 2) < 18.5 
