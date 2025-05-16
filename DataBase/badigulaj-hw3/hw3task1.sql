select 
    rank() over (order by sum(vol) desc) as rank,
    dt,
    sum(vol) as vol
from 
    coins
group by 
    dt
order by 
    vol desc
limit 10;

