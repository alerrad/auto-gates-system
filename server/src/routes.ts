import { Router } from "express";
import { getTimeStamps, addTimeStamp } from "./handlers/timestamp";


export const router = Router();

router.get("/", getTimeStamps);
router.post("/api/timestamp", addTimeStamp);