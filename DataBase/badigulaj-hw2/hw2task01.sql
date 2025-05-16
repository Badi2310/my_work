select full_nm full_name, avg(avg_price) avg_price, max(high_price) max_price, min(low_price) min_price
from coins c
group by full_nm
