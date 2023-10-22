# -*- coding: utf-8 -*-
"""
Created on Fri Oct 13 16:05:28 2023

@author: Matthew Tavares
"""

import openai

# Set your API key
api_key = "YOUR_API_KEY"

# Initialize the OpenAI API client
openai.api_key = api_key

# Accept user input (the word)
user_input = input("Enter a word: ")



user_input = "what is the general pacing, transitions, color correction, and effects of" + user_input + " videos. give specfic  and generalized 1-3 word response for each in the form - (eg. pacing: fast, color correction: warm, effects: slow motion)"




# Generate text using GPT-3.5
response = openai.Completion.create(
    engine="text-davinci-002",  # Choose an appropriate engine
    prompt=f"Generate a text document based on the word: {user_input}",
    max_tokens=100,  # Adjust as needed
)

# Extract the generated text
generated_text = response.choices[0].text

# Save the generated text to a text document
with open("outputEditAI.txt", "w") as file:
    file.write(generated_text)

print("Output saved to output.txt")
