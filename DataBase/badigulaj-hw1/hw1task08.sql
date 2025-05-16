with subquery as (
	select upper(full_nm) full_name, dt, price
	from coins a join
		(select upper(b.full_nm) full_name, max(b.high_price) price
		from coins b
		group by full_name) as bb
	on upper(a.full_nm)=bb.full_name and a.high_price=bb.price
)
select full_name, min(dt) as dt, price from subquery
group by full_name, price
order by price desc, full_name asc;

