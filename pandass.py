import pandas as pandas
import numpy as np
exam_data = { 'name': ["Anastasia","Diana","James","Emily","Laura", "Kevin","JOnas"], 
              'Score': [12.5,9,7.9,10,np.nan],
             'Attempts': [1,1,3,2,3,1,2],
             'qualify': ['yes','no','no','yes','yes','no','yes']
}
Labels = ["a","b","c","d",'e',"f","g"]
df = pd.DataFrame(exam_data, index=labels)
df["age"]=[21,23,24,21,22,29,20]
print(df)
