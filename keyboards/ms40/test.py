import json

with open('info.json', 'r+') as jfile:
    data = json.load(jfile) 
    for idx, key in enumerate(data['layouts']['LAYOUT']['layout']):
        data['layouts']['LAYOUT']['layout'][idx]['y'] = key['y'] + 1.23
            
    json.dump(data, jfile)
