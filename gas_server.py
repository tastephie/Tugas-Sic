from flask import Flask, request, jsonify

app = Flask(__name__)

@app.route('/api/gas', methods=['POST'])
def gas_data():
    data = request.get_json()
    gas_value = data['gas_value']
    
    # Lakukan pemrosesan data sesuai kebutuhan
    # Misalnya, menentukan tingkat konsentrasi gas berdasarkan nilai sensor
    if gas_value < 1000:
        concentration = "Rendah"
    elif gas_value < 2000:
        concentration = "Sedang"
    else:
        concentration = "Tinggi"
    
    response = {"status": "success", "concentration": concentration}
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8000, debug=True)
