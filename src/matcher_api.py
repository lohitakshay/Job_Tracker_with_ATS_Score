from flask import Flask, request, jsonify
import re

app = Flask(__name__)

STOPWORDS = {
    "a", "an", "the", "and", "or", "in", "on", "of", "to", "is", "are", 
    "with", "for", "by", "at", "from", "as", "this", "that", "with", "have"
}

def preprocess(text):
    text = text.lower()
    text = re.sub(r'[^\w\s]', '', text)  # Remove punctuation
    words = [w for w in text.split() if w not in STOPWORDS]
    return set(words)

@app.route('/match', methods=['POST'])
def match():
    resume = request.form['resume']
    jd = request.form['jd']
    
    resume_words = preprocess(resume)
    jd_words = preprocess(jd)
    
    common = resume_words & jd_words
    score = len(common)
    
    return jsonify({'score': score})

if __name__ == '__main__':
    app.run(port=5000)
