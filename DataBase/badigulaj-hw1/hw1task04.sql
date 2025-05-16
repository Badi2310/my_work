SELECT id, bmi,
       CASE 
           WHEN bmi < 18.5 THEN 'underweight'
           WHEN bmi >= 18.5 AND bmi < 25 THEN 'normal'
           WHEN bmi >= 25 AND bmi < 30 THEN 'overweight'
           WHEN bmi >= 30 AND bmi < 35 THEN 'obese'
           WHEN bmi >= 35 THEN 'extremely obese'
       END AS "type"
FROM (
    SELECT id, 703 * 1.0001092375 * weight / POWER(height, 2) AS bmi, weight, height
    FROM hw
) subquery
order by bmi DESC
