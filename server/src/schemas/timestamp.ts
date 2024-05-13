import mongoose, { Schema } from "mongoose";

const timeStampSchema = new Schema({
    gateOpen: {
        type: String,
        required: true,
    },
    gateClosed: {
        type: String,
        required: true,
    }
});

export default mongoose.model("TimeStamp", timeStampSchema);