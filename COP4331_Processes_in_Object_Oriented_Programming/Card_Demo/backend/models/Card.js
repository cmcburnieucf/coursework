const mongoose = require('mongoose');

const cardSchema = new mongoose.Schema({
    Name: {type: String, required: true},
    UserID: {type:Number, default:0}

});

module.exports = mongoose.model('Card', cardSchema);
