import express, { Express } from "express";
import bodyParser from "body-parser";
import mongoose from "mongoose";
import dotenv from "dotenv";

import {router} from "./src/routes";


dotenv.config();

const app: Express = express();
app.use(bodyParser.json());

const PORT = process.env.PORT || 3000;
const MONGO_URI = process.env.MONGO_URI || "";

app.use("/api", router);

app.listen(PORT, async () => {
    try {
        await mongoose.connect(MONGO_URI);
        await mongoose.connection.db.admin().command({ ping: 1 });
        console.info("[server]: Successfully connected to MongoDB!");
    } catch (err) {
        console.error("[server]: Could not connect to MongoDB");
        await mongoose.disconnect();
    }
    console.log(`[server]: Server is running at http://localhost:${PORT}`);
});